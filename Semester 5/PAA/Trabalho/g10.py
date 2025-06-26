import sys
import time
import math
import itertools
import random
from collections import deque
import networkx as nx
import tkinter as tk

cor_map = {
    'vermelho': 'red',
    'azul': 'blue',
    'verde': 'green',
    'amarelo': 'yellow',
    'preto': 'black',
    'branco': 'white',
    'laranja': 'orange',
    'roxo': 'purple',
    'cinza': 'gray'
}

def load_graph(stations_path, lines_path):
    G = nx.Graph()
    
    with open(stations_path, 'r', encoding='utf-8') as f:
        for raw in f:
            line = raw.strip()
            if not line:
                continue
            name, xs, ys = line.split()
            x, y = int(xs), int(ys)
            G.add_node(name, pos=(x, y))
    
    with open(lines_path, 'r', encoding='utf-8') as f:
        while True:
            header = f.readline()
            if not header:
                break  # EOF
            header = header.strip()
            if not header:
                continue  # skip blank lines
            parts = header.split()
            if len(parts) < 3:
                raise ValueError(f"Invalid line header: {header!r}")
            line_id, color, count_s = parts[:3]
            try:
                count = int(count_s)
            except ValueError:
                raise ValueError(f"Invalid connection count in header: {header!r}")
            
            color = cor_map.get(color.lower(), color)

            # read exactly `count` connections
            for _ in range(count):
                conn = f.readline()
                if not conn:
                    raise EOFError("Unexpected end of file reading connections")
                u, v = conn.strip().split()
                if not G.has_node(u) or not G.has_node(v):
                    raise KeyError(f"Station {u!r} or {v!r} not found in stations file")
                # add edge; if multiple lines share the same pair, store as list
                if G.has_edge(u, v):
                    # append to existing attributes
                    G.edges[u, v].setdefault('lines', []).append(line_id)
                    G.edges[u, v].setdefault('colors', []).append(color)
                else:
                    G.add_edge(u, v, line=line_id, color=color, lines=[line_id], colors=[color])
    
    return G

def load_stations(path):
    stations = {}
    with open(path, 'r', encoding='utf-8') as f:
        for raw in f:
            line = raw.strip()
            if not line:
                continue
            name, xs, ys = line.split()
            stations[name] = (float(xs), float(ys))
    return stations

def draw_on_canvas(G, stations, size=(920,920), node_r=8):
    xs = [p[0] for p in stations.values()]
    ys = [p[1] for p in stations.values()]
    minx, maxx = min(xs), max(xs)
    miny, maxy = min(ys), max(ys)
    pad = 50
    sx = (size[0]-2*pad)/(maxx-minx) if maxx>minx else 1
    sy = (size[1]-2*pad)/(maxy-miny) if maxy>miny else 1

    def cvt(p):
        x, y = p
        cx = pad + (x-minx)*sx
        cy = pad + (y - miny) * sy
        return cx, cy

    root = tk.Tk()
    root.title("Map")
    canvas = tk.Canvas(root, width=size[0], height=size[1], bg='white')
    canvas.pack()
    for u, v, data in G.edges(data=True):
        cu, cv = cvt(stations[u]), cvt(stations[v])
        canvas.create_line(cu[0], cu[1], cv[0], cv[1], fill=data['color'], width=4)
    for name, pos in stations.items():
        cx, cy = cvt(pos)
        canvas.create_oval(cx-node_r, cy-node_r, cx+node_r, cy+node_r, fill='white', outline='black')
        canvas.create_text(cx, cy-node_r-2, text=name, anchor=tk.S, font=('TkDefaultFont',8))
    root.mainloop()


# ======================================================
# ============== Minimum 1‐Dominating Set ==============
# ======================================================

def brute_force_min_dominating_set(G): # note! this only returns the first minimum dominating set it finds, not all of them (if there are more than one)
    """
    - dom: current partial dominating set
    - domd: set of nodes already dominated
    search subsets of nodes in increasing size r (from 1 up to |G|)
    for each combination of r nodes:
        - build its domd (dominated set) by taking each node u in the dom, adding u and all of u's neighbors into it
        - if domd covers every node in G, we found a dominating set of size r
    since we try sizes in ascending order, the first hit is guaranteed minimum
    """

    for r in range(1, len(G)+1): # r is the size of the node groups that possibly dominate G (worst case edgeless graph this is |G| nodes)
        for dom in itertools.combinations(G.nodes(), r): # this is the part where it explodes, as it iterate through every combination of size r groups of nodes
            domd = set()
            for u in dom:
                domd |= {u} | set(G.neighbors(u)) # take every neighbour of every node in dom (including themselves) and shove them into a set
            if len(domd) == len(G): # if the lengyh of all nodes in dom summed with all of its neighbours is equal to the size of the graph, it is a min. dom. set
                return set(dom) # this actually works because sets can't have duplicates

def branch_and_bound_min_dominating_set(G):
    """
    - dom: current partial dominating set
    - domd: set of nodes already dominated by dom
    1. If |dom| ≥ best['size'], prune (we already have a better solution).
    2. If |domd| == n, all nodes are dominated, we update best with current dom.
    3. If |dom| + lb ≥ best['size'], prune (even super optimistically we can't beat best).
    4. Choose an undominated node u (first in nodes not in domd).
    5. Branch on two possibilities:
       a) Include u in dom
       b) Include u's neighbours in dom
    """

    nodes = list(G.nodes())
    n = len(nodes)
    neighs = {u:{u}|set(G.neighbors(u)) for u in nodes}
    delta = max(len(neighs[u]) for u in nodes) # maximum number of dominated nodes by a single dominator node
    best = {'size':n+1, 'set':set()}

    def dfs(dom, domd):
        if len(dom) >= best['size']: # current dominating set is already too big
            return

        if len(domd) == n: # all nodes are dominated
            best['size'], best['set'] = len(dom), dom.copy()
            return

        # lower‐bound pruning
        lb = math.ceil((n - len(domd)) / delta) # in other words, lb is the fewest possible dominators needed to dominate the whole stuff
        if len(dom) + lb >= best['size']:
            return

        u = next(x for x in nodes if x not in domd) # branching: pick one undominated node u

        dfs(dom | {u}, domd | neighs[u]) #  try adding u to dominator set

        for v in G.neighbors(u): # try adding one of u's neighbors instead
            if v not in dom:
                dfs(dom | {v}, domd | neighs[v])

    dfs(set(), set())
    return best['set']

def greedy_dominating_set(G):
    """
    - dom : current dominating set (initially empty)
    - domd : set of nodes already dominated (initially empty)
    Repeat until all nodes are dominated:
        1. Select u = the node covering the most undominated nodes.
        2. Add u to dom.
        3. Add u and u's neighbourhood to domd.
    Return dom when domd covers all vertices.
    """

    dom, domd = set(), set()
    while len(domd) < len(G):
        u = max(G.nodes(), key=lambda x: len(({x}|set(G.neighbors(x))) - domd)) # (fancy stuff!) selects the node u who dominates the largest number of undominated nodes
        dom.add(u)
        domd |= {u} | set(G.neighbors(u))
    return dom

# ======================================================
# ================ Longest Simple Cycle ================
# ======================================================

def brute_force_longest_cycle(G, start):
    """
    1. For each neighbour of node:
        a) If node == start and len(path) > 2:
            - A cycle is found; if len(path) > len(best_path), update best_path = path.copy().
        b) Else if neighbour was not visited:
            - Extend path
            - Recurse with extended path
            - Backtrack to try with other paths
    """

    best_path = []

    def dfs(path, visited):
        curr = path[-1]
        for w in G.neighbors(curr):
            if w == start and len(path) > 2: # found a cycle
                if len(path) > len(best_path): # its greater than the current best
                    best_path[:] = path[:]  # current path becomes best path
            elif w not in visited: # there is still a neighbour that wasn't visited - recurse: extend path to neighbour w
                visited.add(w)
                path.append(w)

                dfs(path, visited)

                path.pop() # backtrack - removing the last step from the recursion
                visited.remove(w)

    dfs([start], {start})

    if best_path and (start in G.neighbors(best_path[-1])):
        best_path.append(start)
    
    return best_path

def branch_and_bound_longest_cycle(G, start):
    """
    reachable_count(u, visited):
        Upper-bound: run a BFS from node u (excluding nodes in visited) to count how many additional distinct nodes could still be added to the path at most

    dfs(path):
        1. If len(path) + reachable_count(node, path) <= best['length'], prune (no better cycle possible). <- this is the only practical difference to brute forcing

        2. For each neighbour of node:
            a) If node == start and len(path) > 2:
                - A cycle is found; if len(path) > best['length'], update best
            b) Else if neighbour was not visited:
                - Extend path
                - Recurse with extended path
                - Backtrack to try with other paths
    """

    best = {'length': 0, 'path': []}
    adj = {u: list(G.neighbors(u)) for u in G.nodes()} # creates an adjacency list for each node (adj[u] = [G.neighbors(u)])

    def dfs(path):
        curr = path[-1]

        if len(path) + reachable_count(curr, path) <= best['length']:
            return # if even the optimistic reachable count can't beat current best, stop recursion

        for w in adj[curr]:
            if w == start and len(path) > 2: # found a cycle
                if len(path) > best['length']: # its greater than the current best
                    best['length'] = len(path) # current length becomes best lenght
                    best['path'] = path.copy() # current path becomes best path
            elif w not in path:
                path.append(w)
                dfs(path) 
                path.pop() # backtrack - removing the last step from the recursion

    def reachable_count(u, vis): # upper bound function: a simple BFS that counts all reachable nodes
        seen = set(vis) # copy in all the nodes already on your current path, so you never count them again
        q = deque([u]) # start a BFS (in the form of a double-ended queue, to pop the already explored nodes - in the left - and add its neighbours - in the right) from current node
        seen.add(u)
        cnt = 0
        
        while q:
            x = q.popleft() # take the oldest node
            for y in adj[x]: # iterate through its neighbours
                if y not in seen:
                    seen.add(y)  # mark it so we don’t revisit it
                    q.append(y)  # enqueue it
                    cnt += 1 

        return cnt
    
    dfs([start])

    return best['path'] + [start] if best['path'] and start in adj[best['path'][-1]] else None

def genetic_longest_cycle(G, start, pop_size=50, generations=300, crossover_rate=0.8, mutation_rate=0.2):
    def repair_path(path, G, start):
            # repair function: prune invalid steps (edges that do not exist in G)
            repaired = [start] # always start from `start`
            for node in path:
                if G.has_edge(repaired[-1], node): # check if the edge is valid
                    repaired.append(node)  # keep the node
                else:
                    break # stop at the first invalid step
            return repaired # Return repaired path

    def make_cycle_from_path(path):
        # repair function: try to append `start` to close the path into a valid cycle
        if path and start in G.neighbors(path[-1]):
            return path + [start]
        while len(path) > 1 and start not in G.neighbors(path[-1]):
            path.pop()
        if path and start in G.neighbors(path[-1]):
            return path + [start]
        return None

    def random_cycle():
        # random walk until stuck, then try to close into a cycle
        visited = {start}
        path = [start]
        curr = start
        while True:
            cands = [w for w in G.neighbors(curr) if w not in visited]
            if not cands:
                break
            nxt = random.choice(cands)
            visited.add(nxt)
            path.append(nxt)
            curr = nxt
        cyc = make_cycle_from_path(path.copy())
        return cyc

    def fitness(cycle):
        # length of cycle (excluding the return to start) or 0 if invalid
        if not cycle:
            return 0
        return len(cycle) - 1

    # Initialize population: valid random cycles (fallback to 2-node cycles if needed)
    pop = [random_cycle() for _ in range(pop_size)]
    neighs = list(G.neighbors(start))

    for i in range(len(pop)):
        if pop[i] is None:
            if neighs:
                v = random.choice(neighs)
                pop[i] = [start, v, start]
            else:
                pop[i] = None  # start is isolated — no cycles possible

    best = max(pop, key=fitness) # track the best
    best_fit = fitness(best)

    for gen in range(generations): # main evolutionary loop

        # Selection: tournament of size 2
        selected = []  # store selected individuals for crossover
        for _ in range(pop_size):
            a, b = random.sample(pop, 2)  # randomly pick two individuals
            selected.append(a if fitness(a) >= fitness(b) else b)  # FIGHT TO DEATH!

        # Crossover: OX with validation pruning
        children = []  # store new offspring
        for i in range(0, pop_size, 2):
            p1, p2 = selected[i], selected[i+1]
            if p1 and p2: # only attempt crossover if both parents exist
                commons = set(p1[1:-1]).intersection(p2[1:-1]) # find common intermediate nodes (exclude the fixed 'start' at both ends)
                if commons and random.random() < crossover_rate:
                    cut = random.choice(list(commons))

                    i1 = p1.index(cut)
                    i2 = p2.index(cut)
                    prefix1 = p1[:i1+1]
                    prefix2 = p2[:i2+1]
                    raw_suffix1 = p1[i1+1:]
                    raw_suffix2 = p2[i2+1:]
                    suffix1 = [v for v in raw_suffix1 if v not in prefix2]
                    suffix2 = [v for v in raw_suffix2 if v not in prefix1]
                    child_assembled = prefix1 + suffix2
                    child_assembled2 = prefix2 + suffix1
                    child_repaired = repair_path(child_assembled, G, start)
                    child_repaired2 = repair_path(child_assembled2, G, start)
                    child = make_cycle_from_path(child_repaired)
                    child2 = make_cycle_from_path(child_repaired2)

                    if child is None:
                        child = p1 if fitness(p1) >= fitness(p2) else p2
                        child2 = p1 if fitness(p1) >= fitness(p2) else p2
                else:
                    child = p1 if fitness(p1) >= fitness(p2) else p2
                    child2 = p1 if fitness(p1) >= fitness(p2) else p2

                children.append(child)
                children.append(child2)

        # Mutation: swap-mutation on intermediate nodes
        new_pop = [] # new generation population (after mutation step)
        for cyc in children:  # Iterate over each child from crossover
            if cyc and random.random() < mutation_rate:  # Apply mutation with probability = mutation_rate
                core = cyc[1:-1] # extract the core (exclude start and end, which are both 'start')
                if len(core) >= 2: # mutation only makes sense if there are at least 2 nodes to swap
                    i, j = sorted(random.sample(range(len(core)), 2))  # pick two positions to swap
                    core[i], core[j] = core[j], core[i]  # swap them (python moment)
                mutated = make_cycle_from_path([start] + core)  # repair and close into a valid cycle (if possible)
                if mutated:  # if repair succeeded, use the mutated cycle
                    cyc = mutated
            new_pop.append(cyc)  # add cycle to the new population
        pop = new_pop 

        # best
        for cyc in pop:
            f = fitness(cyc)
            if f > best_fit:
                best, best_fit = cyc, f
                
    return best if best_fit > 0 else None


def grasp(G, start, k=3, iterations=10000):
    """
    1. Repeat for `iterations`:
        - While True:
            + Create list of unvisited neighbours of current node
            + If list is empty:
                # If current node can close the cycle, close it
                # Break loop
            + Else:
                # Sort neighbours by descending degree (more connected first)
                # Restricted candidate list (RCL) picks top-k nodes
                # Pick from RCL at random, visit and append to path
        - If a valid cycle was found and is longer than current best, update it
    2. Return the longest cycle found (or None if no cycle of length ≥ 3 was ever found)
    """

    best_cycle = []

    for _ in range(iterations):
        visited = {start}
        path = [start]
        cycle = None

        while True:
            curr = path[-1]
            cands = [w for w in G.neighbors(curr) if w not in visited]

            if not cands:
                if start in G.neighbors(curr) and len(path) >= 3:
                    cycle = path + [start]
                break

            cands.sort(key=lambda x: G.degree(x), reverse=True)
            rcl = cands[:k]
            nxt = random.choice(rcl)
            visited.add(nxt)
            path.append(nxt)

        if cycle and len(cycle) > len(best_cycle):
            best_cycle = cycle

    return best_cycle if best_cycle else None


def greedy_dfs_cycle(G, start):
    """
    1. While True:
        - Create list of unvisited neighbours of current node
        - If the list is not empty:
            + Choose the node of highest degree
            + Append it to path and mark it as visited
        - Else:
            + Try to return a closeable cycle
            + If none, return None

    Special note from author: worse than all of them, this monstrosity takes the crown. Abhorrent!
    """

    visited = {start}
    path = [start]

    while True:
        curr = path[-1]
        cands = [w for w in G.neighbors(curr) if w not in visited]

        if cands:
            nxt = max(cands, key=lambda w: G.degree(w))
            visited.add(nxt)
            path.append(nxt)
            continue

        if start in G.neighbors(curr) and len(path) >= 3:
            return path + [start]

        return None

    
# kinda cursed kinda bad, maybe one day i fix these 3 algorithms, but that day is not today!

def simulated_annealing_longest_cycle(G, start, T0=1.0, Tmin=1e-4, alpha=0.9, max_iters=1000):
    """
    AS WRITTEN, THIS WILL ONLY WORK FOR COMPLETE GRAPHS (TO.DO: TEST a- reject any neighbor that isnt a real cycle in G, or b- only perform k-opt / insert / swap operations that preserve adjacency)

    Approximate the longest simple cycle in G starting and ending at `start` using simulated annealing.

    Parameters:
    - G: an undirected graph
    - start: the node at which the cycle must begin and end
    - T0: initial temperature
    - Tmin: minimum temperature threshold to halt the annealing
    - alpha: cooling rate
    - max_iters: number of annealing iterations

    Constraints:
    - T0 must be greater than 0. The higher the more accurate and slower
    - Tmin must be greater than 0 - unless you like dividing by 0. The lower the more accurate and slower
    - alpha must be greater than 0 and lower than 1. The higher the more accurate and slower. (realistically, never drop below 0.75)

    Helpers:
    - random_closable_cycle(): this is actually a GARGANTUAN bottleneck, but idk how to fix it so it is what it is tho
        + Builds a random simple path from 'start' by random walks until no unvisited neighbors remain
        + Returns only if the end is adjacent to 'start', then closes it by appending `start`
    - cycle_length(cycle):
        + Returns the number of edges in the cycle
    - two_opt(cycle):
        + Selects i < k and reverses the segment cycle[i:k+1], preserving start/end
    - node_insert(cycle):
        + Removes one intermediate node and reinserts it at a different position (keeping start/end fixed)
    - node_swap(cycle):
        + Swaps two intermediate nodes in place
    - random_neighbor(cycle):
        + Picks one of the above three moves at random, applies it, and checks validity (simple, start==end)

    Outline:
    1. Initialize current and best with randomly generated closable cycle
    2. For up to max_iters iterations:
        a. If T < Tmin, break early
        b. Generate candidate to best using a move at random
        c. Compute delta = cycle_length(candidate) - cycle_length(current)
        d. If (improvement (delta ≥ 0) is always accepted. When Δ < 0, you still accept the worse candidate with a probability which is between 0 and 1.
        At high temperature T, its more likely to accept downhill moves (helps escape local maxima); as T cools, that probability drops) current becomes candidate
        e. If cycle_length(current) > cycle_length(best), update best
        f. Cool: T = alpha*T
    3. Return best cycle (list of nodes, with start repeated at end).
    """

    def random_closable_cycle():
        while True:
            path = [start]
            visited = {start}
            u = start
            while True:
                nbrs = [v for v in G.neighbors(u) if v not in visited]
                if not nbrs:
                    break
                v = random.choice(nbrs)
                path.append(v)
                visited.add(v)
                u = v
            if start in G.neighbors(u) and len(path) > 2:
                return path + [start]

    def cycle_length(cycle):
        return len(cycle) - 1

    def two_opt(cycle):
        n = len(cycle) - 1
        i, k = sorted(random.sample(range(1, n), 2))
        new_cycle = cycle[:i] + cycle[i:k+1][::-1] + cycle[k+1:]
        return new_cycle

    def node_insert(cycle):
        if len(cycle) <= 4:
            return cycle[:]
        i, j = random.sample(range(1, len(cycle)-1), 2)
        c = cycle[:]
        node = c.pop(i)
        c.insert(j, node)
        return c

    def node_swap(cycle):
        if len(cycle) <= 4:
            return cycle[:]
        i, j = random.sample(range(1, len(cycle)-1), 2)
        c = cycle[:]
        c[i], c[j] = c[j], c[i]
        return c

    def random_neighbor(cycle):
        move = random.choice([two_opt, node_insert, node_swap])
        nbr = move(cycle)
        if len(set(nbr[:-1])) == len(nbr)-1 and nbr[0] == nbr[-1]: # no duplicates cycle
            return nbr
        return cycle

    current = random_closable_cycle()
    best = current[:]
    T = T0

    for _ in range(max_iters):
        if T < Tmin:
            break
        candidate = random_neighbor(current)
        delta = cycle_length(candidate) - cycle_length(current)
        if delta >= 0 or random.random() < math.exp(delta / T):
            current = candidate
            if cycle_length(current) > cycle_length(best):
                best = current[:]
        T *= alpha

    return best

def tabu_search_longest_cycle(G, start, tabu_tenure=10, max_iters=100, neigh_sample=50):
    """
    Parameters:
    - G: undirected graph
    - start: the node at which every cycle must begin and end
    - tabu_tenure: maximum size of the tabu list (number of forbidden moves)
    - max_iters: maximum number of iterations to perform
    - neigh_sample: number of neighbor moves to sample for 2-opt and swap

    Helpers:
    - random_closable_cycle(): this is actually a GARGANTUAN bottleneck, but idk how to fix it so it is what it is tho
        + Builds a random simple path from 'start' by random walks until no unvisited neighbors remain
        + Returns only if the end is adjacent to 'start', then closes it by appending `start`
    - cycle_length(cycle):
        + Returns the number of edges in the cycle
    - neighbors(cycle):
        • Generates up to `neigh_sample` 2-opt reversals and `neigh_sample//2` node swaps.
        • Only returns valid simple cycles (start==end, no repeated intermediate nodes).


    Outline:
    1. Initialize current = random_closable_cycle(), best_global = current.
    2. Initialize empty tabu list of maxlen = tabu_tenure.
    3. For up to max_iters:
        a. Generate a list of candidate moves with neighbors(current).
        b. Filter out moves whose move_id is in tabu, unless they improve best_global.
        c. If no candidates remain, terminate early.
        d. Select the neighbor with maximum cycle_length as the new current.
        e. Append its move_id to tabu.
        f. If current is better than best_global, update best_global.
    4. Return best_global (list of nodes, with start at both ends).
    """

    def random_closable_cycle():
        while True:
            path = [start]
            visited = {start}
            u = start
            while True:
                nbrs = [v for v in G.neighbors(u) if v not in visited]
                if not nbrs:
                    break
                v = random.choice(nbrs)
                path.append(v)
                visited.add(v)
                u = v
            if start in G.neighbors(u) and len(path) > 2:
                return path + [start]

    def cycle_length(cycle):
        return len(cycle)-1

    def neighbors(cycle):
        nbrs=[]
        n=len(cycle)-1
        for _ in range(neigh_sample):
            i,k=sorted(random.sample(range(1,n),2))
            c2=cycle[:i]+cycle[i:k+1][::-1]+cycle[k+1:]
            if len(set(c2[:-1]))==len(c2)-1:
                nbrs.append(("2-opt", i, k, c2))
        for _ in range(neigh_sample//2):
            i,j=random.sample(range(1,n),2)
            c2=cycle[:]; c2[i],c2[j]=c2[j],c2[i]
            if len(set(c2[:-1]))==len(c2)-1:
                nbrs.append(("swap", i, j, c2))
        return nbrs

    current = random_closable_cycle()
    best_global = current[:]
    tabu = deque(maxlen=tabu_tenure)

    for it in range(max_iters):
        cand_moves = neighbors(current)
        filtered = []
        for m,i,j,c in cand_moves:
            move_id = (m, i, j)
            if move_id not in tabu or cycle_length(c) > cycle_length(best_global):
                filtered.append((move_id, c))
        if not filtered:
            break
        move_id, best_nb = max(filtered, key=lambda x: cycle_length(x[1]))
        tabu.append(move_id)
        current = best_nb
        if cycle_length(current) > cycle_length(best_global):
            best_global = current[:]

    return best_global

def aco_longest_cycle(G, start, num_ants=20, num_iters=100, alpha=1.0, beta=2.0, rho=0.1, Q=1.0):
    """
    Parameters:
    - G         : undirected graph (e.g., networkx.Graph)
    - start     : node at which every cycle must begin and end
    - num_ants  : number of ants (candidate solutions) per iteration
    - num_iters : number of ACO iterations
    - alpha     : pheromone importance exponent
    - beta      : heuristic importance exponent
    - rho       : pheromone evaporation rate (0 < rho < 1)
    - Q         : total pheromone deposited per iteration

    Data structures:
    - tau       : nested dict of pheromone levels, tau[u][v] initialized to 1.0 for each edge
    - heuristic : function returning 1/deg(v) (or 1 if deg(v)=0) as desirability of choosing v

    Helpers:
    - construct_cycle():
        - Starts at `start`, builds a simple path by repeatedly choosing the next node from unvisited neighbors or closing back to `start` if possible.
        - Selection probability ∝ (tau[u][v]^alpha)·(heuristic(u, v)^beta).
    - Returns a closable cycle [start, …, start] or None if no closure.

    Main ACO loop:
    1. For each iteration:
       a. Each of num_ants ants runs construct_cycle(); collect all successful cycles.
       b. Let best_it be the longest cycle found this iteration.
       c. Update global best_cycle if best_it is longer.
       d. Evaporate pheromone: tau[u][v] ← (1 - rho)·tau[u][v] for all edges.
       e. Deposit pheromone along edges of best_cycle: τ[u][v] += Q / L, where L = cycle length.

    Return:
    - best_cycle: list of nodes closing at `start` (e.g. [start, …, start]) if found
    - Fallback: if no cycle ever found, returns a trivial 2-cycle [start, v, start] for any neighbor v,
      or empty list if `start` is isolated.
    """
        
    tau = {u: {v: 1.0 for v in G[u]} for u in G}

    def heuristic(u, v):
        return 1.0 / (G.degree(v) or 1)

    def construct_cycle():
        path = [start]; visited={start}; u = start
        while True:
            nbrs = [v for v in G.neighbors(u) if v not in visited]
            closers = [v for v in G.neighbors(u) if v == start and len(path) > 2]
            choices = nbrs + closers
            if not choices:
                break
            probs = []
            for v in choices:
                p = (tau[u][v]**alpha) * (heuristic(u, v)**beta)
                probs.append(p)
            s = sum(probs)
            r = random.random() * s
            cum = 0
            for v, p in zip(choices, probs):
                cum += p
                if r <= cum:
                    nxt = v
                    break
            if nxt == start:
                return path + [start]
            path.append(nxt); visited.add(nxt); u = nxt
        return None

    best_cycle = None

    for it in range(num_iters):
        all_cycles = []
        for _ in range(num_ants):
            c = construct_cycle()
            if c is not None:
                all_cycles.append(c)
        if not all_cycles:
            continue
        best_it = max(all_cycles, key=lambda c: len(c))
        if best_cycle is None or len(best_it) > len(best_cycle):
            best_cycle = best_it[:]
        for u in tau:
            for v in tau[u]:
                tau[u][v] *= (1 - rho)
        L = len(best_cycle) - 1
        for u, v in zip(best_cycle[:-1], best_cycle[1:]):
            tau[u][v] += Q / L
            tau[v][u] += Q / L

    # this sux very bad
    if best_cycle is None:
        for v in G.neighbors(start):
            return [start, v, start]
        return []

    return best_cycle

# ======================================================
# ===================== Main/Menu ======================
# ======================================================

def main():
    if len(sys.argv) != 3:
        print(f"Usagw: python {sys.argv[0]} <stations.txt> <lines.txt>")
        sys.exit(1)

    sf = sys.argv[1]
    stations = load_stations(sf)
    G = load_graph(sys.argv[1], sys.argv[2])

    while True:
        print("Select functionality:")
        print("  1- Draw Graph")
        print("  2- Minimum 1-Dominating Set")
        print("  3- Longest Simple Cycle")
        print("  4- Exit")
        choice = input(" > ").strip()
        
        if choice == '1':
            draw_on_canvas(G, stations)
            print("")

        elif choice == '2':
            print("\nSelect algorithm(s) ('all' to run all) (comma separated):")
            print("  1- Brute Force (this may take forever)")
            print("  2- Branch-and-Bound (this may take a long time)")
            print("  3- Greedy")
            algs = input(" > ").strip().lower()

            if algs == 'all':
                sel = {'1','2','3'}
            else:
                sel = set(token for token in algs.replace(' ','').split(',') if token in ('1','2','3'))
            if not sel:
                print("No valid choice. Exiting.")
                sys.exit(1)

            print("\n--- Minimum 1-Dominating Set Results ---\n")

            if "1" in sel:
                start = time.perf_counter()
                bf_dom = brute_force_min_dominating_set(G)
                dur = time.perf_counter() - start
                print(f"Brute Force:")
                print(f"  Size = {len(bf_dom)}")
                print(f"  Set  = {bf_dom}")
                print(f"  Time = {dur:.3f} s\n")

            if "2" in sel:
                start = time.perf_counter()
                bnb_dom = branch_and_bound_min_dominating_set(G)
                dur = time.perf_counter() - start
                print(f"Branch-and-Bound:")
                print(f"  Size = {len(bnb_dom)}")
                print(f"  Set  = {bnb_dom}")
                print(f"  Time = {dur:.3f} s\n")

            if "3" in sel:
                start = time.perf_counter()
                greedy_dom = greedy_dominating_set(G)
                dur = time.perf_counter() - start
                print(f"Greedy:")
                print(f"  Size = {len(greedy_dom)}")
                print(f"  Set  = {greedy_dom}")
                print(f"  Time = {dur:.3f} s\n")
                

        elif choice == '3':
            start = input("\nStarting node (blank to auto-select best (this may take a while)): ").strip()

            if start and start not in G:
                print(f"Node '{start}' not in graph.")
                sys.exit(1)

            print("Select algorithm(s) to run (comma separated) ('WIP' to see WIP options) ('all' to run all 'nobf' to run all except brute force): ")
            print("  1- Brute Force")
            print("  2- Branch-and-Bound")
            print("  3- Genetic Algorithm")
            print("  4- Greedy DFS")
            print("  5- Greedy Random-Restart")

            algs = input(" > ").strip().lower()

            valid = {"1","2","3","4","5"}
            valid_except_bf = {"2", "3", "4", "5"}

            if algs == "wip":
                valid = {"1","2","3","4","5","6","7","8"}
                print("  6- Simulated Annealing (WIP)")
                print("  7- Tabu Search (WIP)")
                print("  8- Ant Colony (WIP)")
                algs = input(" > ").strip().lower()


            if algs == "all":
                algs = sorted(valid)
            elif algs == "nobf":
                algs = sorted(valid_except_bf)
            else:
                algs = sorted(token for token in algs.replace(" ", "").split(",") if token in valid)

            if not algs:
                print("No valid option selected. Exiting.")
                sys.exit(1)

            funcs = {
                "1": brute_force_longest_cycle,
                "2": branch_and_bound_longest_cycle,
                "3": genetic_longest_cycle,
                "4": greedy_dfs_cycle,
                "5": grasp,
                "6": simulated_annealing_longest_cycle,
                "7": tabu_search_longest_cycle,
                "8": aco_longest_cycle,
            }

            names = {
                "1": "Brute Force",
                "2": "Branch-and-Bound",
                "3": "Genetic Algorithm",
                "4": "Greedy DFS",
                "5": "Greedy Random-Restart",
                "6": "Simulated Annealing",
                "7": "Tabu Search",
                "8": "Ant Colony",
            }

            print("\n--- Longest Simple Cycle ---\n")

            for key in algs:
                func = funcs[key]
                name = names[key]

                startTime = time.perf_counter()
                if start:
                    path = func(G, start)
                    if path is None:
                        closed = []
                    elif path and path[-1] != start and start in G.neighbors(path[-1]):
                        closed = path + [start]
                    else:
                        closed = path[:]
                    length = len(closed)
                    start_loc = start
                else:
                    best = {'start': None, 'length': 0, 'path': []}
                    for u in G.nodes():
                        p = func(G, u)
                        if p is None:
                            continue
                        if p and p[-1] != u and u in G.neighbors(p[-1]):
                            p_closed = p + [u]
                        else:
                            p_closed = p
                        if p_closed:
                            l = len(p_closed)
                            if l > best['length']:
                                best = {'start': u, 'length': l, 'path': p}

                    start_loc = best['start']
                    bp = best['path'] or []
                    if bp and bp[-1] != start_loc and start_loc in G.neighbors(bp[-1]):
                        closed = bp + [start_loc]
                    else:
                        closed = bp[:]
                    length = len(closed)

                dur = time.perf_counter() - startTime

                print(f"{name}:")
                print(f"  Starting Location = {start_loc}")
                print(f"  Length            = {length}")
                print(f"  Path              = {closed}")
                print(f"  Time              = {dur:.3f} s\n")

        
        elif choice == '4':
            print("Exiting.\n")
            break

        else:
            print("Invalid option. Exiting.")
            sys.exit(1)

if __name__ == '__main__':
    main()
