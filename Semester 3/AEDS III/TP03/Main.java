import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
   public static String lerArquivo(String caminhoArquivo) throws IOException {
      StringBuilder conteudo = new StringBuilder();

      BufferedReader leitor = new BufferedReader(new FileReader(caminhoArquivo));
      String linha;
      while ((linha = leitor.readLine()) != null) {
         conteudo.append(linha);
         conteudo.append("\n");
      }
      leitor.close();

      return conteudo.toString();
   }

   public static int version = 0;

   public static void main(String args[]) throws IOException, ClassNotFoundException {
      CifraSubstituicao substituicao = new CifraSubstituicao();
      CifraCesar cesar = new CifraCesar(3);
      Scanner fetch = new Scanner(System.in);
      CRUD crud = new CRUD("pokemonDB");
      String basefile = "pokemonSample.csv";
      System.out.println("Deseja carregar o arquivo?");
      System.out.println("1-Sim \n2-Nao");
      try {
         if (fetch.nextInt() == 1) {
            FileInputStream fs = new FileInputStream(basefile);
            BufferedReader br = new BufferedReader(new InputStreamReader(fs));
            String csvLine = br.readLine();
            while ((csvLine = br.readLine()) != null) {
               Pokemon pokemon = new Pokemon();
               pokemon.parseCSV(csvLine);
               crud.create(pokemon);
            }
            br.close();
         }
      } catch (Exception e) {
         System.out.println("error");
      }
      int choice = 0;
      while (choice != 7) {
         System.out.println("Escolha uma operação: ");
         System.out.println("1- Create");
         System.out.println("2- Read");
         System.out.println("3- Update");
         System.out.println("4- Delete");
         System.out.println("5- Compress");
         System.out.println("6- Decompress");
         System.out.println("7- Sair");
         choice = fetch.nextInt();

         switch (choice) {

            // CREATE
            case 1:
               try {
                  String gen = "";
                  String hiddenAbility = "";
                  String date = "";
                  System.out.println("Digite o ID: ");
                  int readID = fetch.nextInt();
                  String lixo = fetch.nextLine();
                  if (crud.search(readID)) {
                     // Personalizar para meu CSV e campos de Pokemon
                     System.out.println("Digite o nome do Pokemon: ");
                     String pokemonName = fetch.nextLine();
                     System.out.println("Digite o número da pokedex: ");
                     int pokedexID = fetch.nextInt();
                     lixo = fetch.nextLine();
                     System.out.println("Escreva o número da geração: ");
                     gen = fetch.nextLine();

                     System.out.println("Escreva o nome da especie de Pokemon: ");
                     String specie = fetch.nextLine();

                     System.out.println("Escreva o nome da habilidade escodida: ");
                     hiddenAbility = fetch.nextLine();
                     // data
                     System.out.println("Digite a data de lançamento do Pokemon: ");
                     System.out.println("Ex.: yyyy-MM-dd");
                     date = fetch.nextLine();

                     // arrays types
                     System.out.println("Escreva os tipos do pokemon (separado por virgulas)");
                     System.out.println("Ex: Fire, Rock");
                     String typesStr = fetch.nextLine();
                     String[] types = typesStr.split(",");
                     ArrayList<String> typesAL = new ArrayList<String>();
                     for (int i = 0; i < types.length; i++) {
                        typesAL.add(types[i]);
                     }
                     // abilities
                     System.out.println("Escreva as habilidades do Pokemon (separado por virgulas)");
                     System.out.println("Keen Eye, Tangled Feet");
                     String abilitiesStr = fetch.nextLine();
                     String[] abilities = abilitiesStr.split(",");
                     ArrayList<String> abilitiesAL = new ArrayList<String>();
                     for (int i = 0; i < abilities.length; i++) {
                        abilitiesAL.add(types[i]);
                     }
                     Pokemon pokemon = new Pokemon();
                     String line = readID + "," + pokedexID + "," + pokemonName + "," + gen + "," + specie + ","
                           + hiddenAbility + "," + date + ",\"" + typesStr + "\"," + "\"" + abilitiesStr + "\"";
                     System.out.println(line);
                     pokemon.parseCSV(line);
                     crud.create(pokemon);
                     System.out.println("\nArquivo atualizado!\n");

                     System.out.print(
                           "ID: " + pokemon.getIndex() + ", Pokedex ID: " + pokemon.getPokedexNum()
                                 + ", Nome do Pokemon: " + pokemon.getName()
                                 + ", Geração: " + pokemon.getGeneration()
                                 + ", Especie: " + pokemon.getSpecie()
                                 + ", Hidden Hability: " + pokemon.getHiddenAbility() + ", ");

                     System.out.print("Tipos: ");
                     for (int i = 0; i < pokemon.getTypes().size(); i++) {
                        System.out.print(pokemon.getTypes().get(i) + " ");
                     }
                     System.out.print(" Habilidades: ");
                     for (int i = 0; i < pokemon.getAbilities().size(); i++) {
                        System.out.print(pokemon.getAbilities().get(i) + " ");
                     }
                     System.out.println("");
                     System.out.println("");
                  } else
                     System.out.println("ID já existente.");
               } catch (Exception e) {
                  System.out.println("Erro ao criar Arquivo.");
               }

               break;
            case 2:
               try {
                  System.out.println("Digite o ID: ");
                  int readID = fetch.nextInt();
                  Pokemon pokemon = crud.Read(readID);
                  if (pokemon.lapide) {
                     System.out.print(
                           "ID: " + pokemon.getIndex() + ", Pokedex ID: " + pokemon.getPokedexNum()
                                 + ", Nome do Pokemon: " + pokemon.getName()
                                 + ", Geração: " + pokemon.getGeneration()
                                 + ", Especie: " + pokemon.getSpecie()
                                 + ", Hidden Hability: " + pokemon.getHiddenAbility() + ", ");

                     System.out.print("Tipos: ");
                     for (int i = 0; i < pokemon.getTypes().size(); i++) {
                        System.out.print(pokemon.getTypes().get(i) + " ");
                     }
                     System.out.print(" Habilidades: ");
                     for (int i = 0; i < pokemon.getAbilities().size(); i++) {
                        System.out.print(pokemon.getAbilities().get(i) + " ");
                     }
                     System.out.println("");
                  } // Teste para ver se pokemon existe (teste de pointer)
                  else
                     System.out.println("Arquivo não Encontrado!");
                  ;
               } catch (Exception e) {
                  System.out.println("\nArquivo não encontrado!");
               }

               break;

            // Update
            case 3:
               System.out.print("Digite o ID do Pokemon que deseja atualizar no arquivo: ");
               int updateID = fetch.nextInt();
               String lixo = fetch.nextLine();
               boolean checkArq;
               try {
                  crud.delete(updateID);
                  checkArq = true;
               } catch (Exception e) {
                  checkArq = false;
               }
               if (!checkArq) {
                  System.out.println("\nO arquivo não existe!");
                  break;
               }
               System.out.println("Digite o nome do Pokemon: ");
               String pokemonName = fetch.nextLine();
               System.out.println("Digite o número da pokedex: ");
               int pokedexID = fetch.nextInt();
               lixo = fetch.nextLine();
               System.out.println("Escreva o número da geração: ");
               String gen = fetch.nextLine();

               System.out.println("Escreva o nome da especie de Pokemon: ");
               String specie = fetch.nextLine();

               System.out.println("Escreva o nome da habilidade escodida: ");
               String hiddenAbility = fetch.nextLine();
               // data
               System.out.println("Digite a data de lançamento do Pokemon: ");
               System.out.println("Ex.: yyyy-MM-dd");
               String date = fetch.nextLine();

               // arrays types
               System.out.println("Escreva os tipos do pokemon (separado por virgulas)");
               System.out.println("Ex: Fire, Rock");
               String typesStr = fetch.nextLine();
               String[] types = typesStr.split(",");
               ArrayList<String> typesAL = new ArrayList<String>();
               for (int i = 0; i < types.length; i++) {
                  typesAL.add(types[i]);
               }
               // abilities
               System.out.println("Escreva as habilidades do Pokemon (separado por virgulas)");
               System.out.println("Keen Eye, Tangled Feet");
               String abilitiesStr = fetch.nextLine();
               String[] abilities = abilitiesStr.split(",");
               ArrayList<String> abilitiesAL = new ArrayList<String>();
               for (int i = 0; i < abilities.length; i++) {
                  abilitiesAL.add(types[i]);
               }
               Pokemon pokemon = new Pokemon();
               String line = updateID + "," + pokedexID + "," + pokemonName + "," + gen + "," + specie + ","
                     + hiddenAbility + "," + date + ",\"" + typesStr + "\"," + "\"" + abilitiesStr + "\"";
               System.out.println(line);
               pokemon.parseCSV(line);
               crud.create(pokemon);
               System.out.println("\nRegistro atualizado com sucesso!");
               // Enviar para Update no CRUD
               break;

            // Delete

            case 4:
               System.out.print("Digite o ID do Pokemon que deseja deletar no arquivo: ");
               int deleteID = fetch.nextInt();
               try {
                  Pokemon pokemonDeleted = crud.Read(deleteID); // Teste para ver se existe Pokemon
                  System.out.print(
                        "ID: " + pokemonDeleted.getIndex() + ", Pokedex ID: " + pokemonDeleted.getPokedexNum()
                              + ", Nome do pokemon deletado: " + pokemonDeleted.getName()
                              + ", Geração: " + pokemonDeleted.getGeneration()
                              + ", Especie: " + pokemonDeleted.getSpecie()
                              + ", Hidden Hability: " + pokemonDeleted.getHiddenAbility() + ", ");

                  System.out.print("Tipos: ");
                  for (int i = 0; i < pokemonDeleted.getTypes().size(); i++) {
                     System.out.print(pokemonDeleted.getTypes().get(i) + " ");
                  }
                  System.out.print(" Habilidades: ");
                  for (int i = 0; i < pokemonDeleted.getAbilities().size(); i++) {
                     System.out.print(pokemonDeleted.getAbilities().get(i) + " ");
                  }
                  System.out.println("");
                  crud.delete(deleteID); // Deleta o Pokemon
                  System.out.println("\nArquivo deletado com sucesso!");
               } catch (Exception e) {
                  System.out.println("\nArquivo não encontrado!");
               }
               // Enviar para Delete no CRUD
               break;
            case 5:
               // Ciframento de César
               BufferedWriter bwCesar = new BufferedWriter(new FileWriter("Cesar.txt"));
               String caminhoArquivo = basefile;
               String conteudoBanco = lerArquivo(caminhoArquivo);
               String txtCifradoCesar = cesar.cifrar(conteudoBanco);
               bwCesar.write(txtCifradoCesar);
               bwCesar.close();
               // Cifra por substituição

               String txtCifradoSubstituicao = substituicao.criptografa(conteudoBanco);
               FileWriter crip = new FileWriter("substituicao.txt");
               crip.write(txtCifradoSubstituicao);
               crip.close();
               System.out.println("Arquivos criptografados com sucesso!\n");
               break;
            case 6:
               // Cesar
               int chaveCesarDecrip = 3;
               CifraCesar cesarDecript = new CifraCesar(chaveCesarDecrip);
               BufferedReader brCesar = new BufferedReader(new FileReader("Cesar.txt"));
               String lineCesar;
               StringBuilder strBuilder = new StringBuilder();
               while ((lineCesar = brCesar.readLine()) != null) {
                  strBuilder.append(lineCesar);
                  strBuilder.append("\n");
               }
               String cesarDecrip = strBuilder.toString();
               cesarDecrip = cesarDecript.decifrar(cesarDecrip); // Descriptografia.
               brCesar.close();
               FileWriter escreveCesar = new FileWriter("Cesar.txt");
               escreveCesar.write(cesarDecrip);
               escreveCesar.close();

               // Cifra por substituição
               try {
                  // Abre arquivo criptografado para leitura
                  BufferedReader reader = new BufferedReader(new FileReader("substituicao.txt"));
                  StringBuilder textoCriptografadoBuilder = new StringBuilder();
                  String linhaArq;
                  while ((linhaArq = reader.readLine()) != null) {
                     // Lê todo arquivo e salva em um String Builder
                     textoCriptografadoBuilder.append(linhaArq);
                     textoCriptografadoBuilder.append("\n");
                  }
                  reader.close();
                  // Converte String Builder para String
                  String textoCriptografado = textoCriptografadoBuilder.toString();

                  // Descriptografa o texto
                  String textoDescriptografado = substituicao.descriptografa(textoCriptografado);

                  // Sobrescreve o arquivo com o texto descriptografado
                  FileWriter writer = new FileWriter("substituicao.txt");
                  writer.write(textoDescriptografado);
                  writer.close();

                  System.out.println("Arquivos descriptografados com sucesso!\n");
               } catch (IOException e) {
                  System.out.println("Erro ao ler ou escrever no arquivo");
                  e.printStackTrace();
               }
               break;
            case 7:

               break;
         }

      }
      fetch.close();
   }
}
