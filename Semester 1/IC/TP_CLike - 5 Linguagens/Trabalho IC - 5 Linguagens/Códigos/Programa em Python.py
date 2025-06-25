#Trabalho IC em 5 Linguagens - Linguagem C++ 
#Autor - Gabriel Azevedo Fernandes
#Data - 12/06/2022


núm = int(input('Digite um número:'))
tot = 0
for c in range(1,núm+1):
  if núm %c == 0:
    print('\033[33m', end =' ')
    tot +=1
  else:
    print('\033[31m', end=' ')
  print('{}'.format(c), end=' ')
print('\033[m\n0 número {} foi divisível {} vezes'.format(núm,tot))
if tot == 2:
  print('E por isso ele é PRIMO!')
else:
  print('E por isso ele NÃO É PRIMO!')