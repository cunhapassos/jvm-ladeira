/**
 * @file interpretador.h
 * @brief Arquivo cabeçalho da implementação das instruções e funções auxiliares.
 */

 #ifndef INTERPRETADOR_H
#define INTERPRETADOR_H

#include "instrucoes.h"
#include "classFileStruct.h"
#include "jvm.h"
#include <stdbool.h>

/** Macro para normalizar índice do pool de constantes */
#define normaliza_indice(x,y) (x << 8) | y

/**
 * @brief Função para resolver (analisar e alocar caso nao alocada) uma classe
 * 
 * @param nome_classe Nome da classe a ser resolvida
 * @return Ponteiro para a classe resolvida
 */
ClassFile* resolverClasse(char *nome_classe);

/**
 * @brief Função para resolver (analisar parâmetros, nome e descriptor) método
 * 
 * @param cp Ponteiro para constant pool
 * @param indice_cp Índice a ser acessado na constante pool
 * @param interface Flag para sinalizar método de interface
 * @return Valor booleano representando o sucesso da execucção da resolução
 */
bool resolverMetodo(cp_info *cp, u2 indice_cp, u1 interface);

/**
 * @brief Função para obter o nome de um método na constant pool
 * 
 * @param cp Ponteiro para constant pool
 * @param indice_cp Índice a ser acessado na constante pool
 * @param interface Flag para sinalizar método de interface
 * @return Ponteiro de char representando a string contendo o nome do método
 */
char* obterNomeMetodo(cp_info *cp, u2 indice_cp, u1 interface);

/**
 * @brief Função para obter o descriptor de um método
 * 
 * @param cp Ponteiro para constant pool
 * @param indice_cp Índice a ser acessado na constante pool
 * @param interface Flag para sinalizar método de interface
 * @return Ponteiro de char representando a string contendo o descriptor do método
 */
char* obterDescriptorMetodo(cp_info *cp, u2 indice_cp, u1 interface);

/**
 * @brief Função para obter o tipo do descriptor do método
 * 
 * @param descriptor Ponteiro de char representando a string contendo o descriptor do método
 * @return Valor inteiro representando o tipo do descriptor do método
 */
int descriptorFieldValidate (char * descriptor);

/**
 * @brief Função para obter a classe executante de um método
 * 
 * @param cp Ponteiro para constant pool
 * @param indice_cp Índice a ser acessado na constante pool
 * 
 * @return Ponteiro de char representando a string contendo o nome da classe de um método
 */
char* obterClasseDoMetodo(cp_info *cp, u2 indice_cp);

/**
 * @brief Função para transferir os valores da pilha de operandos de um frame para o vetor de variáveis locais do próximo frame
 * 
 * @param anterior Frame anterior (previamente executado)
 * @param novo Frame novo sendo alocado para execução de método
 * @param parametros_cont Contador de parâmetros a serem passados para o array de variáveis locais do novo frame
 * @return Retorna um ponteiro para frame, com o array de variáveis locais atualizado
 */
frame* transferePilhaVetor(frame *anterior, frame *novo, int *parametros_cont);

/**
 * @brief Função para decodificar operandos em um valor double (64 bits)
 * 
 * @param high Parte alta do valor double (32 bits)
 * @param low Parte baixa do valor double (32 bits)
 * 
 * @return Valor double decodificado
 */
double decodificaDoubleValor(u4 high, u4 low);

/**
 * @brief Função para decodificar operando em um valor float (32 bits)
 * 
 * @param valor 4 bytes do tipo unsigned representando o valor float
 * @return Valor float decodificado
 */
float decodificaFloatValor(u4 valor);

/**
 * @brief Função para decodificar operandos em um valor long (64 bits)
 * 
 * @param high Parte alta do valor long (32 bits)
 * @param low Parte baixa do valor long (32 bits)
 * 
 * @return Valor long decodificado
 */
long decodificaLongValor (u4 high, u4 low);

/**
 * @brief Função para obter a quantidade de campos da classe que não são estáticos (atributos de classe)
 * 
 * @param classe Ponteiro para a classe alocada
 * @return Valor inteiro com a quantidade de campos que não são do tipo static
 */
int getParametrosNaoStatic (ClassFile * classe);

/**
 * @brief Função para inserir um objeto novo na lista de objetos
 * 
 * @param lis Ponteiro para o começo da lista de objetos
 * @param classe Referência para a classe (objeto) a ser alocada na lista
 * @param parametrosNaoStatic Quantidade de parâmetros que não são static
 * @return Ponteiro para a lista de objetos atualizado com a inserção do novo objeto
 */
Lista_Objetos * InsereObjeto (Lista_Objetos * lis, ClassFile * classe, int parametrosNaoStatic);

/**
 * @brief Função para verificar se um método ou field é do tipo static
 * 
 * @param accessFlags String contendo o accessflags do método ou field
 * @return Valor booleano indicando que o método ou field é do tipo static
 */
bool buscaStaticFlags (char * accessFlags);

/**
 * @brief Função para obter a quantidade de parâmetros a serem passados para um método
 * 
 * @param descriptor String contendo o descriptor do método (parâmetros e tipo de retorno)
 * @return Valor inteiro representando a quantidade de parâmetros a serem passados para o método
 */
int getParametrosCount (char * descriptor);

/**
 * @brief Função para buscar um objeto na lista de objetos
 * 
 * @param p Ponteiro de classe contendo a referência ao objeto
 * @return Retorna um ponteiro para a lista de objetos
 */
Lista_Objetos * buscaObjetoViaReferencia (ClassFile * p);

/**
 * @brief Função para obter a posição do field no array de dados de instância (dados não estáticos)
 * 
 * @param obj Ponteiro para o objeto alocado
 * @param nomeField Nome do field pertencente ao objeto
 * 
 * @return Posição do field no array de dados não estáticos
 */
int getPositionField (ClassFile * obj, char * nomeField);

/**
 * @brief Função para instanciar um objeto novo
 * 
 * @param nomeClasse Ponteiro para char contendo a string do nome da classe
 * @return Ponteiro para o objeto alocado
 */
ClassFile * instanciarClasse (char * nomeClasse);

/**
 * @brief Função para obter o tipo do operando a ser alocado na pilha de operandos
 * 
 * @param descriptorRetorno Ponteiro de char contendo a string que representa o descriptor do método
 * @return Valor inteiro representando o tipo do operando a ser alocado na pilha de operandos
 */
int getTipoOperandoSaida(char * descriptorRetorno);

/**
 * @brief Função para obter o modo de empilhamento do valor de retorno de um método
 * 
 * @param descriptor Ponteiro de char contendo a string que representa o descriptor do método
 * @return Valor inteiro representando o modo de empilhamento do valor de retorno de um método na pilha de operandos
 */
int getTipoRetorno (char * descriptor);


/**
 * @brief Não executa nada =)
 * 
 * @param par0 -
 * @param par1 -
 * @param par2 -
 */
void nop_impl(frame *par0,u1 par1, u1 par2);
/**
 * @brief Faz o push de um valor nulo para a pilha de operandos 
 * @param f Ponteiro para o frame]
 * @param par1 -
 * @param par2 -
 */
void aconst_null_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param f [description]
 * @param par1 [description]
 * @param par2 [description]
 */
void iconst_m1_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Faz o push para a pilha de operando da constante 0 \c int
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void iconst_0_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Faz o push para a pilha de operando da constante 1 \c int
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void iconst_1_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Faz o push para a pilha de operando da constante 2 \c int
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void iconst_2_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Faz o push para a pilha de operando da constante 3 \c int
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void iconst_3_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Faz o push para a pilha de operando da constante 4 \c int
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void iconst_4_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Faz o push para a pilha de operando da constante 5 \c int
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void iconst_5_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Faz o push para a pilha de operando da constante 0 \c long
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void lconst_0_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Faz o push para a pilha de operando da constante 1 \c long
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void lconst_1_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Faz o push para a pilha de operando da constante 0 \c float
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void fconst_0_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Faz o push para a pilha de operando da constante 1 \c float
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void fconst_1_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Faz o push para a pilha de operando da constante 2 \c float
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void fconst_2_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Faz o push para a pilha de operando da constante 0 \c double
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void dconst_0_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Faz o push para a pilha de operando da constante 1 \c double
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void dconst_1_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Faz o push de um byte na pilha de operandos
 * 
 * @param f Ponteiro para o frame
 * @param byte Byte a ser empilhado
 * @param par1 -
 */
void bipush_impl(frame *f, u1 byte, u1 par1);
/**
 * @brief Faz o push de um short na pilha de operandos
 * 
 * @param f Ponteiro para o frame
 * @param byte Primeiro byte do short
 * @param par1 Segundo byte do short
 */
void sipush_impl(frame *f,u1 byte1, u1 byte2);
/**
 * @brief Faz o push de um valor presente na constant pool
 * @param f Ponteiro para o frame
 * @param indexbyte1 Índice da constant pool
 * @param par2 -
 */
void ldc_impl(frame *f,u1 indexbyte1,u1 par2);
/**
 * @brief Faz o push de um valor presente na constant pool
 * @param f Ponteiro para o frame
 * @param indexbyte1 Índice da constant pool (primeira parte)
 * @param indexbyte2 Índice da constant pool (segunda parte)
 */
void ldc_w_impl(frame *f, u1 indexbyte1, u1 indexbyte2);
/**
 * @brief Faz o push de um valor long ou double presente na constant pool
 * @param f Ponteiro para o frame
 * @param branchbyte1 Índice da constant pool (primeira parte)
 * @param branchbyte2 Índice da constant pool (segunda parte)
 */
void ldc2_w_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
/**
 * @brief Carrega um valor \c int do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param index Índice no vetor de variáveis locais
 * @param par1 -
 */
void iload_impl(frame *f, u1 index, u1 par1);
/**
 * @brief Carrega um valor \c long do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param index Índice no vetor de variáveis locais
 * @param par1 -
 */
void lload_impl(frame *f, u1 index, u1 par1);
/**
 * @brief Carrega um valor \c float do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param index Índice no vetor de variáveis locais
 * @param par1 -
 */
void fload_impl(frame *f, u1 index, u1 par1);
/**
 * @brief Carrega um valor \c double do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param index Índice no vetor de variáveis locais
 * @param par1 -
 */
void dload_impl(frame *par0, u1 par1,u1 par2);
/**
 * @brief Carrega uma referência do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param index Índice no vetor de variáveis locais
 * @param par1 -
 */
void aload_impl(frame *f, u1 index, u1 par1);
/**
 * @brief Carrega um valor \c int da posição 0 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par2 -
 * @param par1 -
 */
void iload_0_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Carrega um valor \c int da posição 1 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par2 -
 * @param par1 -
 */
void iload_1_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Carrega um valor \c int da posição 2 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par2 -
 * @param par1 -
 */
void iload_2_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Carrega um valor \c int da posição 3 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par2 -
 * @param par1 -
 */
void iload_3_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Carrega um valor \c long da posição 0 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par2 -
 * @param par1 -
 */
void lload_0_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Carrega um valor \c long da posição 1 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par2 -
 * @param par1 -
 */
void lload_1_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Carrega um valor \c long da posição 2 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par2 -
 * @param par1 -
 */
void lload_2_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Carrega um valor \c long da posição 3 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par2 -
 * @param par1 -
 */
void lload_3_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Carrega um valor \c float da posição 0 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par2 -
 * @param par1 -
 */
void fload_0_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Carrega um valor \c float da posição 1 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par2 -
 * @param par1 -
 */
void fload_1_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Carrega um valor \c float da posição 2 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par2 -
 * @param par1 -
 */
void fload_2_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Carrega um valor \c float da posição 3 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par2 -
 * @param par1 -
 */
void fload_3_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Carrega um valor \c double da posição 0 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par2 -
 * @param par1 -
 */
void dload_0_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Carrega um valor \c double da posição 1 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par2 -
 * @param par1 -
 */
void dload_1_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Carrega um valor \c double da posição 2 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par2 -
 * @param par1 -
 */
void dload_2_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Carrega um valor \c double da posição 3 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par2 -
 * @param par1 -
 */
void dload_3_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Carrega uma referência da posição 0 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par2 -
 * @param par1 -
 */
void aload_0_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Carrega uma referência da posição 1 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par2 -
 * @param par1 -
 */
void aload_1_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Carrega uma referência da posição 2 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par2 -
 * @param par1 -
 */
void aload_2_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Carrega uma referência da posição 3 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par2 -
 * @param par1 -
 */
void aload_3_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Carrega um \c int de um array
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void iaload_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Carrega um \c long de um array
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void laload_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Carrega um \c float de um array
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void faload_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Carrega um \c double de um array
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void daload_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Carrega uma referência de um array
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void aaload_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Carrega um \c byte de um array
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void baload_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Carrega um \c char de um array
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void caload_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Carrega um \c short de um array
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void saload_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Armazena um \c int no vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param index Índice do vetor de variáveis locais
 */
void istore_impl(frame *f, u1 index, u1 par1);
/**
 * @brief Armazena um \c long no vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param index Índice do vetor de variáveis locais
 */
void lstore_impl(frame *f, u1 index, u1 par1);
/**
 * @brief Armazena um \c float no vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param index Índice do vetor de variáveis locais
 */
void fstore_impl(frame *f, u1 index, u1 par1);
/**
 * @brief Armazena um \c double no vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param index Índice do vetor de variáveis locais
 */
void dstore_impl(frame *f, u1 index, u1 par1);
/**
 * @brief Armazena uma referência no vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param index Índice do vetor de variáveis locais
 */
void astore_impl(frame *f,u1 index, u1 par1);
/**
 * @brief Armazena um \c int na posição 0 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void istore_0_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Armazena um \c int na posição 1 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void istore_1_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Armazena um \c int na posição 2 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void istore_2_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Armazena um \c int na posição 3 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void istore_3_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Armazena um \c long na posição 0 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void lstore_0_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Armazena um \c long na posição 1 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void lstore_1_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Armazena um \c long na posição 2 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void lstore_2_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Armazena um \c long na posição 3 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void lstore_3_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Armazena um \c float na posição 0 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void fstore_0_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Armazena um \c float na posição 1 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void fstore_1_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Armazena um \c float na posição 2 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void fstore_2_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Armazena um \c float na posição 3 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void fstore_3_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Armazena um \c double na posição 0 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void dstore_0_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Armazena um \c double na posição 1 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void dstore_1_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Armazena um \c double na posição 2 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void dstore_2_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Armazena um \c double na posição 3 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void dstore_3_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Armazena uma referência na posição 0 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void astore_0_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Armazena uma referência na posição 1 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void astore_1_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Armazena uma referência na posição 2 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void astore_2_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Armazena uma referência na posição 3 do vetor de variáveis locais
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void astore_3_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Armazena um valor \c int em um array
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void iastore_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Armazena um valor \c long em um array
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void lastore_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Armazena um valor \c float em um array
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void fastore_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Armazena um valor \c double em um array
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void dastore_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Armazena uma referência em um array
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void aastore_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Armazena um valor \c byte em um array
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void bastore_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Armazena um valor \c char em um array
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void castore_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Armazena um valor \c short em um array
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void sastore_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Remove o valor de topo da pilha de operandos
 * 
 * @param f Ponteiro para o frame
 */
pilha_operandos* pop_impl(frame *f);
/**
 * @brief Remove os dois valores de topo da pilha de operandos
 * 
 * @param f Ponteiro para o frame
 */
pilha_operandos** pop2_impl(frame *f);
/**
 * @brief PlaceHolder para ocupar posicao no vetor de posicoes da instrucao pop
 * @details [long description]
 * 
 * @param par0 frame.
 * @param par1 -
 * @param par2 -
 */
void pop_fantasma(frame *par0, u1 par1, u1 par2);
/**
 * @brief PlaceHolder para ocupar posicao no vetor de posicoes da instrucao pop2
 * @details [long description]
 * 
 * @param par0 frame.
 * @param par1 -
 * @param par2 -
 */
void pop2_fantasma(frame *par0, u1 par1, u1 par2);
/**
 * @brief Duplica o valor no topo da pilha de operandos.
 * @details [long description]
 * 
 * @param f frame.
 * @param par1 -
 * @param par2 -
 */
void dup_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Duplica o valor no topo da pilha de operandos e insere dois valores a baixo.
 * @details [long description]
 * 
 * @param f frame.
 * @param par1 -
 * @param par2 -
 */
void dup_x1_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Duplica o valor no topo da pilha de operandos e insere dois ou três valores a baixo.
 * @details [long description]
 * 
 * @param f frame.
 * @param par1 -
 * @param par2 -
 */
void dup_x2_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Duplica o primeiro ou o segundo valor no topo da pilha de operandos e insere logo abaixo.
 * @details [long description]
 * 
 * @param f frame.
 * @param par1 -
 * @param par2 -
 */
void dup2_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Duplica o primeiro ou o segundo valor no topo da pilha de operandos e insere dois valores a baixo.
 * @details [long description]
 * 
 * @param f frame.
 * @param par1 -
 * @param par2 -
 */
void dup2_x1_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Duplica o primeiro ou o segundo valor no topo da pilha de operandos e insere dois ou três valores a baixo.
 * @details [long description]
 * 
 * @param f frame.
 * @param par1 -
 * @param par2 -
 */
void dup2_x2_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Inverte os dois operandos do topo da pilha
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void swap_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Executa uma soma de \c int
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void iadd_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Executa uma soma de \c long
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void ladd_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Executa uma soma de \c float
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void fadd_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Executa uma soma de \c double
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void dadd_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Executa uma subtração de \c int
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void isub_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Executa uma subtração de \c long
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void lsub_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Executa uma subtração de \c float
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void fsub_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Executa uma subtração de \c double
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void dsub_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Executa uma multiplicação de \c int
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void imul_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Executa uma multiplicação de \c long
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void lmul_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Executa uma multiplicação de \c float
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void fmul_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Executa uma multiplicação de \c double
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void dmul_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Executa uma divisão de \c int
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void idiv_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Executa uma divisão de \c long
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void ldiv_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Executa uma divisão de \c float
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void fdiv_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Executa uma divisão de \c double
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void ddiv_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Calcula o resto \c int da divisão entre dois operandos
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void irem_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Calcula o resto \c long da divisão entre dois operandos
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void lrem_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Calcula o resto \c float da divisão entre dois operandos
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void frem_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Calcula o resto \c double da divisão entre dois operandos
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void drem_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Inverte o sinal de um \c int
 * 
 * @param f Ponteiro para o frame
 * @param par1 -		
 * @param par2 -
 */
void ineg_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Inverte o sinal de um \c long
 * 
 * @param f Ponteiro para o frame
 * @param par1 -		
 * @param par2 -
 */
void lneg_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Inverte o sinal de um \c float
 * 
 * @param f Ponteiro para o frame
 * @param par1 -		
 * @param par2 -
 */
void fneg_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Inverte o sinal de um \c double
 * 
 * @param f Ponteiro para o frame
 * @param par1 -		
 * @param par2 -
 */
void dneg_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Executa um shift left em um \c int
 * 
 * @param f Ponteiro para o frame
 * @param par1 -		
 * @param par2 -
 */
void ishl_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Executa um shift left em um \c long
 * 
 * @param f Ponteiro para o frame
 * @param par1 -		
 * @param par2 -
 */
void lshl_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Executa um shift right em um \c int
 * 
 * @param f Ponteiro para o frame
 * @param par1 -		
 * @param par2 -
 */
void ishr_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Executa um shift right em um \c long
 * 
 * @param f Ponteiro para o frame
 * @param par1 -		
 * @param par2 -
 */
void lshr_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Executa um shift right lógico em um \c int
 * 
 * @param f Ponteiro para o frame
 * @param par1 -		
 * @param par2 -
 */
void iushr_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Executa um shift right lógico em um \c long
 * 
 * @param f Ponteiro para o frame
 * @param par1 -		
 * @param par2 -
 */
void lushr_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Executa a operação "AND" de dois \c int
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void iand_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Executa a operação "AND" de dois \c long
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void land_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Executa a operação "OR" de dois \c int
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void ior_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Executa a operação "OR" de dois \c long
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void lor_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Executa a operação "XOR" de dois \c int
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void ixor_impl(frame *f, u1 par1, u1 par2);
/**
 * @brief Executa a operação "XOR" de dois \c long
 * 
 * @param f Ponteiro para o frame
 * @param par1 -
 * @param par2 -
 */
void lxor_impl(frame *f, u1 par1, u1 par2);
void iinc_fantasma(frame *par0, u1 par1, u1 par2);
void iinc_impl(frame *f, u1 index, i1 constante);
void iinc_wide_fantasma(frame *f, u1 indexbyte1, u1 indexbyte2, u1 constbyte1, u1 constbyte2);
void iinc_wide(frame *f, u2 indexbyte, i2 constbyte);
void i2l_impl(frame *f, u1 par1, u1 par2);
void i2f_impl(frame *f, u1 par1, u1 par2);
void i2d_impl(frame *f, u1 par1, u1 par2);
void l2i_impl(frame *f, u1 par1, u1 par2);
void l2f_impl(frame *f, u1 par1, u1 par2);
void l2d_impl(frame *f, u1 par1, u1 par2);
void f2i_impl(frame *f, u1 par1, u1 par2);
void f2l_impl(frame *f, u1 par1, u1 par2);
void f2d_impl(frame *f, u1 par1, u1 par2);
void d2i_impl(frame *f, u1 par1, u1 par2);
void d2l_impl(frame *f, u1 par1, u1 par2);
void d2f_impl(frame *f, u1 par1, u1 par2);
void i2b_impl(frame *f, u1 par1, u1 par2);
void i2c_impl(frame *f, u1 par1, u1 par2);
void i2s_impl(frame *f, u1 par1, u1 par2);
void lcmp_impl(frame *f, u1 par1, u1 par2);
void fcmpl_impl(frame *f, u1 par1, u1 par2);
void fcmpg_impl(frame *f, u1 par1, u1 par2);
void dcmpl_impl(frame *f, u1 par1, u1 par2);
void dcmpg_impl(frame *f, u1 par1, u1 par2);
void ifeq_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void ifne_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void iflt_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void ifge_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void ifgt_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void ifle_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void if_icmpeq_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void if_icmpne_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void if_icmplt_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void if_icmpge_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void if_icmpgt_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void if_icmple_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void acmpeq_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void acmpne_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void inst_goto_impl(frame *f,u1 branchbyte1, u1 branchbyte2);
void jsr_impl(frame *f,u1 branchbyte1, u1 branchbyte2);
void ret_impl(frame *f, u1 index, u1 par1);
void tableswitch_fantasma(frame *par0, u1 par1, u1 par2);
void lookupswitch_fantasma(frame *par0, u1 par1, u1 par2);
void tableswitch_impl(frame *f);
void lookupswitch_impl(frame *f);
void ireturn_impl(frame *f, u1 par1, u1 par2);
void lreturn_impl(frame *f, u1 par1, u1 par2);
void freturn_impl(frame *f, u1 par1, u1 par2);
void dreturn_impl(frame *f, u1 par1, u1 par2);
void areturn_impl(frame *f, u1 par1, u1 par2);
void inst_return_impl(frame *f, u1 par1, u1 par2);
void getstatic_impl(frame *f, u1 indexbyte1, u1 indexbyte2);
void putstatic_impl(frame *f, u1 indexbyte1, u1 indexbyte2);
void getfield_impl(frame *f, u1 indexbyte1, u1 indexbyte2);
void putfield_impl(frame *f, u1 indexbyte1, u1 indexbyte2);
void invokevirtual_impl(frame *f, u1 indexbyte1, u1 indexbyte2);
void invokespecial_impl(frame *f, u1 indexbyte1, u1 indexbyte2); // Não implementado
void invokestatic_impl(frame *f, u1 indexbyte1, u1 indexbyte2);
void invokeinterface_fantasma(frame *par0, u1 par1, u1 par2);
void invokeinterface_impl(frame *f, u1 indexbyte1, u1 indexbyte2, u1 count);
void invokedynamic_fantasma(frame *par0, u1 par1, u1 par2); // Não implementado. /** Essa instrução só existe para criar uma posição "falsa" no vetor de ponteiros de função **/
void inst_new_impl(frame *f, u1 indexbyte1, u1 indexbyte2);
void newarray_impl(frame *f ,u1 atype, u1 par1); // Observação do -INT_MAX
void anewarray_impl(frame *f, u1 par1, u1 par2); // Não implementado
void arraylength_impl(frame *f, u1 par1, u1 par2);
void athrow_impl(frame *f, u1 par1, u1 par2); // Não implementado - ESSAS SÃO OPCIONAIS
void checkcast_impl(frame *f, u1 par1, u1 par2); // Não implementado - ESSAS SÃO OPCIONAIS
void instanceof_impl(frame *f, u1 par1, u1 par2); // Não implementado - ESSAS SÃO OPCIONAIS
void monitorenter_impl(frame *f, u1 par1, u1 par2); // Não implementado - ESSAS SÃO OPCIONAIS
void monitorexit_impl(frame *f, u1 par1, u1 par2); // Não implementado - ESSAS SÃO OPCIONAIS
void wide_impl(frame *f, u1 indexbyte1, u1 indexbyte2); // Não implementado
void multianewarray_impl(frame *f, u1 indexbyte1, u1 indexbyte2, u1 dimensions); // Não implementado
void multianewarray_fantasma(frame *f, u1 par1, u1 par2); // Não implementado
void ifnull_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void ifnonnull_impl(frame *f, u1 branchbyte1, u1 branchbyte2);
void goto_w_impl(frame *f, u1 par1, u1 par2);
void jsr_w_impl(frame *f, u1 par1, u1 par2);

extern void (*func_ptr[202])(frame *,u1,u1);

#endif
