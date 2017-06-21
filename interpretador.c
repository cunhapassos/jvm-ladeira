/*
	Observar os comentários das instruções. Praticamente todas precisam ser finalizadas.
	Entender como acessar a constant pool, e como fazer as invocações de métodos, obtenção de fields e campos static, etc.
*/

#include "interpretador.h"
#include "jvm.h"
#include "leitura.h"
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

bool resolverClasse(char* nome_classe){
	classesCarregadas *c = BuscarElemento_classes(jvm->classes,nome_classe);

	if(c!=NULL){
		return true;
	}
	else{
		return false;
	}

}

/*
	Depois da resolverMetodo, analisar semanticamente. Ver o número de argumentos, o tipo deles, ver se está tudo coerente com o descritor do método.
*/
bool resolverMetodo(cp_info *cp, u2 indice_cp){

	cp_info *methodref = cp-1+indice_cp;
	char *nome_classe = decodificaNIeNT(cp,methodref->UnionCP.Methodref.class_index,NAME_INDEX);
	char *descriptor = decodificaNIeNT(cp,methodref->UnionCP.Methodref.name_and_type_index,NAME_AND_TYPE);

	if(resolverClasse(nome_classe)){
		return true;
	}
	else{
		return false;
	}
}

char* obterClasseDoMetodo(cp_info *cp, u2 indice_cp){
	cp_info *methodref = cp-1+indice_cp;
	char *nome_classe = decodificaNIeNT(cp,methodref->UnionCP.Methodref.class_index,NAME_INDEX);
	return(nome_classe);
}

frame* transferePilhaVetor(frame *anterior, frame *novo){
	pilha_operandos *aux = CriarPilha_operandos();
	int cont = 0;
	printf("\n\n\nANTES WHILE\n\n\n");
	while(anterior->p->topo!=NULL){
		pilha_operandos *p = Pop_operandos(anterior->p);
		printf("\n\n\nTIROU: %d\n\n\n",p->topo->operando);
		aux = Push_operandos(aux,p->topo->operando,p->topo->tipo_operando);
		cont++;
	}



	novo->v = malloc(cont*sizeof(vetor_locais));

	for(int i=0;i<cont;i++){
		pilha_operandos *p = Pop_operandos(aux);
		novo->v[i].variavel = malloc(sizeof(u4));
		*(novo->v[i].variavel) = (u4) p->topo->operando;
		novo->v[i].tipo_variavel = (u1) p->topo->tipo_operando;
	}

	return(novo);
}

void nop_impl(frame *par0, u1 par1, u1 par2){
	// Não implementada
}

void aconst_null_impl(frame *f, u1 par1, u1 par2){
	Push_operandos(f->p,0,REFERENCE_OP); // 0 do tipo referência quer dizer referência apontando para NULL
}

void iconst_m1_impl(frame *f, u1 par1, u1 par2){
	i4 inteiro_sinal = (i4) -1;
	Push_operandos(f->p,inteiro_sinal,INTEGER_OP);
}

void iconst_0_impl(frame *f, u1 par1, u1 par2){
	i4 inteiro_sinal = (i4) 0;
	Push_operandos(f->p,inteiro_sinal,INTEGER_OP);
}

void iconst_1_impl(frame *f, u1 par1, u1 par2){
	i4 inteiro_sinal = (i4) 1;
	Push_operandos(f->p,inteiro_sinal,INTEGER_OP);
}

void iconst_2_impl(frame *f, u1 par1, u1 par2){
	i4 inteiro_sinal = (i4) 2;
	Push_operandos(f->p,inteiro_sinal,INTEGER_OP);
}

void iconst_3_impl(frame *f, u1 par1, u1 par2){
	i4 inteiro_sinal = (i4) 3;
	Push_operandos(f->p,inteiro_sinal,INTEGER_OP);
}

void iconst_4_impl(frame *f, u1 par1, u1 par2){
	i4 inteiro_sinal = (i4) 4;
	Push_operandos(f->p,inteiro_sinal,INTEGER_OP);
}

void iconst_5_impl(frame *f, u1 par1, u1 par2){
	i4 inteiro_sinal = (i4) 5;
	Push_operandos(f->p,(u4)inteiro_sinal,INTEGER_OP);
}

void lconst_0_impl(frame *f, u1 par1, u1 par2){

	//Push 0L to stack
	i4 high_bytes = (i4) 0;
	Push_operandos(f->p,high_bytes,LONG_OP);

	//TOPO DA PILHA FICA O LOW
	i4 low_bytes = (i4) 0;
	Push_operandos(f->p,low_bytes,LONG_OP);
}

void lconst_1_impl(frame *f, u1 par1, u1 par2){

	//Push 1L to stack 
	i4 high_bytes = (i4) 0;
	Push_operandos(f->p,high_bytes,LONG_OP);

	//TOPO DA PILHA FICA O LOW
	i4 low_bytes = (i4) 1;
	Push_operandos(f->p,low_bytes,LONG_OP);
}

void fconst_0_impl(frame *f, u1 par1, u1 par2){

	i4 float_bytes = (i4) 0;
	Push_operandos(f->p,float_bytes,FLOAT_OP);

}

void fconst_1_impl(frame *f, u1 par1, u1 par2){

	i4 float_bytes = 0x3f800000;
	Push_operandos(f->p,float_bytes,FLOAT_OP);

}

void fconst_2_impl(frame *f, u1 par1, u1 par2){

	i4 float_bytes = 0x40000000;
	Push_operandos(f->p,float_bytes,FLOAT_OP);

}

void dconst_0_impl(frame *f, u1 par1, u1 par2){

	//Push 0.0 double to stack
	i4 high_bytes = (i4) 0;
	Push_operandos(f->p,high_bytes,DOUBLE_OP);

	//TOPO DA PILHA FICA O LOW
	i4 low_bytes = (i4) 0;
	Push_operandos(f->p,low_bytes,DOUBLE_OP);
}

void dconst_1_impl(frame *f, u1 par1, u1 par2){

	//Push 1.0 double to stack
	i4 high_bytes = 0x3FF00000;	
	Push_operandos(f->p,high_bytes,DOUBLE_OP);

	//TOPO DA PILHA FICA O LOW
	i4 low_bytes = (i4) 0;
	Push_operandos(f->p,low_bytes,DOUBLE_OP);
}

void bipush_impl(frame *f, u1 byte, u1 par1){
	i4 byte_int = (i4) byte;
	Push_operandos(f->p,byte_int,BYTE_OP);
}

void sipush_impl(frame *f, u1 byte1, u1 byte2){
	u2 byte_short = (byte1 << 8) | byte2;
	i4 byte_int = (i4) byte_short;
	Push_operandos(f->p,byte_int,SHORT_OP);
	Push_operandos(f->p,byte_int,SHORT_OP);
}

void ldc_impl(frame *par0, u1 par1, u1 par2){

}

void ldc_w_impl(frame *par0, u1 par1, u1 par2){

}

void ldc2_w_impl(frame *par0, u1 par1, u1 par2){

}

void iload_impl(frame *f, u1 index, u1 par1){
	Push_operandos(f->p,(i4) *(f->v[index].variavel),INTEGER_OP);
}

void lload_impl(frame *f, u1 index, u1 par1){

}

void fload_impl(frame *f, u1 index, u1 par1){
	Push_operandos(f->p, (i4) *(f->v[index].variavel),FLOAT_OP);
}

void dload_impl(frame *par0, u1 par1, u1 par2){

}

void aload_impl(frame *f, u1 index, u1 par1){
	Push_operandos(f->p, (i4) *(f->v[index].variavel),REFERENCE_OP);
}

void iload_0_impl(frame *f, u1 par1, u1 par2){
	Push_operandos(f->p,(i4) *(f->v[0].variavel),INTEGER_OP);
}

void iload_1_impl(frame *f, u1 par1, u1 par2){
	Push_operandos(f->p,(i4) *(f->v[1].variavel),INTEGER_OP);
}

void iload_2_impl(frame *f, u1 par1, u1 par2){
	Push_operandos(f->p,(i4) *(f->v[2].variavel),INTEGER_OP);
}

void iload_3_impl(frame *f, u1 par1, u1 par2){
	Push_operandos(f->p,(i4) *(f->v[3].variavel),INTEGER_OP);
}

void lload_0_impl(frame *f, u1 par1, u1 par2){

}

void lload_1_impl(frame *f, u1 par1, u1 par2){

}

void lload_2_impl(frame *f, u1 par1, u1 par2){

}

void lload_3_impl(frame *f, u1 par1, u1 par2){

}

void fload_0_impl(frame *f, u1 par1, u1 par2){
	Push_operandos(f->p,(i4) *(f->v[0].variavel),FLOAT_OP);
}

void fload_1_impl(frame *f, u1 par1, u1 par2){
	Push_operandos(f->p,(i4) *(f->v[1].variavel),FLOAT_OP);
}

void fload_2_impl(frame *f, u1 par1, u1 par2){
	Push_operandos(f->p,(i4) *(f->v[2].variavel),FLOAT_OP);
}

void fload_3_impl(frame *f, u1 par1, u1 par2){
	Push_operandos(f->p,(i4) *(f->v[3].variavel),FLOAT_OP);
}

void dload_0_impl(frame *f, u1 par1, u1 par2){
	
}

void dload_1_impl(frame *f, u1 par1, u1 par2){
	
}

void dload_2_impl(frame *f, u1 par1, u1 par2){

}

void dload_3_impl(frame *f, u1 par1, u1 par2){

}

void aload_0_impl(frame *f, u1 par1, u1 par2){
	Push_operandos(f->p,(i4) *(f->v[0].variavel),REFERENCE_OP);
}

void aload_1_impl(frame *f, u1 par1, u1 par2){
	Push_operandos(f->p,(i4) *(f->v[1].variavel),REFERENCE_OP);
}

void aload_2_impl(frame *f, u1 par1, u1 par2){
	Push_operandos(f->p,(i4) *(f->v[2].variavel),REFERENCE_OP);
}

void aload_3_impl(frame *f, u1 par1, u1 par2){
	Push_operandos(f->p,(i4) *(f->v[3].variavel),REFERENCE_OP);
}


/* Verificar endereçamento */
/* Vale para iaload a saload */
void iaload_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *referencia = Pop_operandos(f->p);

	i4 endereco;
	endereco = ((i4) referencia->topo->operando) + (indice->topo->operando * sizeof(i4));

	// Objetivo: Acessar o conteúdo do endereço "referencia+indice"
	// O código para esse acesso não parece correto, tem que analisar
	Push_operandos(f->p,endereco,INTEGER_OP);
}

void laload_impl(frame *f, u1 par1, u1 par2){

}

void faload_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *referencia = Pop_operandos(f->p);

	i4 endereco;
	endereco = ((i4) referencia->topo->operando) + (indice->topo->operando * sizeof(i4));

	// Acessar o conteúdo do endereço "referencia+indice"
	// O código para esse acesso não parece correto, tem que analisar
	Push_operandos(f->p,endereco,FLOAT_OP);
}

void daload_impl(frame *f, u1 par1, u1 par2){

}

void aaload_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *referencia = Pop_operandos(f->p);

	u4 endereco;
	endereco = ((u4) referencia->topo->operando) + (indice->topo->operando * sizeof(u4));

	Push_operandos(f->p,endereco,REFERENCE_OP);
}

void baload_impl(frame *f, u1 par1, u1 par2){

	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *referencia = Pop_operandos(f->p);

	i1 endereco;
	endereco = ((i1) referencia->topo->operando) + (indice->topo->operando * sizeof(i1));
	i1 byte = endereco;
	//O Sign Extend foi feito?
	Push_operandos(f->p,(i4) byte,BYTE_OP);
}

void caload_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *referencia = Pop_operandos(f->p);

	u2 endereco;
	endereco = ((u2) referencia->topo->operando) + (indice->topo->operando * sizeof(u2));
	u2 caracter = endereco;
	//O Zero Extend foi feito?
	Push_operandos(f->p,(u4) caracter,CHAR_OP);
}

void saload_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *referencia = Pop_operandos(f->p);

	i2 endereco;
	endereco = ((i2) referencia->topo->operando) + (indice->topo->operando * sizeof(i2));
	i2 ashort = endereco;
	//O Sign Extend foi feito?
	Push_operandos(f->p,(i4) ashort,SHORT_OP);
}

void istore_impl(frame *f, u1 index,u1 par1){
	pilha_operandos *valor = Pop_operandos(f->p);

	*(f->v[index].variavel) = (u4) valor->topo->operando;
}

void lstore_impl(frame *f, u1 index, u1 par1){

}

void fstore_impl(frame *f, u1 index,u1 par1){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[index].variavel) = (u4) valor->topo->operando;
}

void dstore_impl(frame *f, u1 index, u1 par1){

}

void astore_impl(frame *f, u1 index,u1 par1){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[index].variavel) = (u4) valor->topo->operando;
}

void istore_0_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[0].variavel) = (u4) valor->topo->operando;
}

void istore_1_impl(frame *f, u1 par1, u1 par2){

	printf("EXECUÇÃO ISTORE_1\n\n");

	/*pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[1].variavel) = (u4) valor->topo->operando;*/
}

void istore_2_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[2].variavel) = (u4) valor->topo->operando;
}

void istore_3_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[3].variavel) = (u4) valor->topo->operando;
}

void lstore_0_impl(frame *f, u1 par1, u1 par2){

}

void lstore_1_impl(frame *f, u1 par1, u1 par2){

}

void lstore_2_impl(frame *f, u1 par1, u1 par2){

}

void lstore_3_impl(frame *f, u1 par1, u1 par2){

}

void fstore_0_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[0].variavel) = (u4) valor->topo->operando;
}

void fstore_1_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[1].variavel) = (u4) valor->topo->operando;
}

void fstore_2_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[2].variavel) = (u4) valor->topo->operando;
}

void fstore_3_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[3].variavel) = (u4) valor->topo->operando;
}

void dstore_0_impl(frame *f, u1 par1, u1 par2){

}

void dstore_1_impl(frame *f, u1 par1, u1 par2){

}

void dstore_2_impl(frame *f, u1 par1, u1 par2){

}

void dstore_3_impl(frame *f, u1 par1, u1 par2){

}

void astore_0_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[0].variavel) = (u4) valor->topo->operando;
}

void astore_1_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[1].variavel) = (u4) valor->topo->operando;
}

void astore_2_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[2].variavel) = (u4) valor->topo->operando;
}

void astore_3_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor = Pop_operandos(f->p);
	*(f->v[3].variavel) = (u4) valor->topo->operando;
}

/*
	Objetivo da instrução: atribuir um valor a uma posição de um array de inteiros
	Exemplo: v[2] = 3.
	Pegar o endereço de v, somar com 2 "endereços de v" e o valor dessa posição de memória será igual a 3.
	
	Não sabemos se isso está logicamente/semanticamente correto.
*/
void iastore_impl(frame *f, u1 par1, u1 par2){
	// Convém criar função pra desempilhar 3 valores, sei lá. Pra generalizar isso. Vamos analisar.
	pilha_operandos *valor = Pop_operandos(f->p);
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *array = Pop_operandos(f->p);

	i4 endereco;
	endereco = ((i4) array->topo->operando) + (indice->topo->operando * sizeof(i4));

	endereco = valor->topo->operando;
}

void lastore_impl(frame *f, u1 par1, u1 par2){

}

void fastore_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor = Pop_operandos(f->p);
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *array = Pop_operandos(f->p);

	i4 endereco;
	endereco = ((i4) array->topo->operando) + (indice->topo->operando * sizeof(i4));

	endereco = valor->topo->operando;
}

void dastore_impl(frame *f, u1 par1, u1 par2){

}

void aastore_impl(frame *f, u1 par1, u1 par2){

}

void bastore_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor = Pop_operandos(f->p);
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *array = Pop_operandos(f->p);

	i1 endereco;
	endereco = ((i1) array->topo->operando) + (indice->topo->operando * sizeof(i1));

	endereco = valor->topo->operando;
}

void castore_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor = Pop_operandos(f->p);
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *array = Pop_operandos(f->p);

	u2 endereco;
	endereco = ((u2) array->topo->operando) + (indice->topo->operando * sizeof(u2));

	endereco = valor->topo->operando;
}

void sastore_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor = Pop_operandos(f->p);
	pilha_operandos *indice = Pop_operandos(f->p);
	pilha_operandos *array = Pop_operandos(f->p);

	i2 endereco;
	endereco = ((i2) array->topo->operando) + (indice->topo->operando * sizeof(i2));

	endereco = valor->topo->operando;
}

pilha_operandos* pop_impl(frame *f){
	pilha_operandos *valor = Pop_operandos(f->p);

	return(valor);
}

pilha_operandos** pop2_impl(frame *f){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	pilha_operandos **vetor_retorno = malloc(2*sizeof(pilha_operandos));
	vetor_retorno[0] = valor1;	
	vetor_retorno[1] = valor2;	

	// Optamos por não montar o valor aqui, pois depende da instrução seguinte, que realizará alguma operação
	// A instrução de operação com os valores manipula do jeito que a gente precisar.
	/*// Se for categoria 2
	if(valor1->topo->tipo_operando == DOUBLE_OP || valor1->topo->tipo_operando == LONG_OP){
		vetor_retorno[0]->topo = malloc
	}
	// Se for categoria 1
	else{

	}*/

	return(vetor_retorno);
}

void pop_fantasma(frame *par0, u1 par1, u1 par2){

}

void pop2_fantasma(frame *par0, u1 par1, u1 par2){

}

void dup_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor = Topo_operandos(f->p);
	f->p = Push_operandos(f->p,valor->topo->operando,valor->topo->tipo_operando);
}

void dup_x1_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor2->topo->operando,valor2->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->tipo_operando);
}

void dup_x2_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);
	pilha_operandos *valor3 = Pop_operandos(f->p);

	// Se for categoria 2
	// Teoricamente não precisa desse if
	// Se valor2 for categoria 2, tem que desempilhar o próximo
	// Se não for, também tem que desempilhar o próximo 
	/*if(valor2->topo->tipo_operando == LONG_OP || valor2->topo->tipo_operando == DOUBLE_OP){

	}
	else{

	}*/

	// Valor 1,3,2,1 ou 1,2,1
	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->tipo_operando);
	// Se valor2 for categoria 2, valor3 e valor2 se referem ao mesmo número
	f->p = Push_operandos(f->p,valor3->topo->operando,valor3->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor2->topo->operando,valor2->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->tipo_operando);
}

void dup2_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	// Se for 32 ou 64 bits, não faz diferença, como na instrução anterior.
	// Porém, verificar se isso é valido.
	f->p = Push_operandos(f->p,valor2->topo->operando,valor2->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor2->topo->operando,valor2->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->tipo_operando);
}

void dup2_x1_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);
	pilha_operandos *valor3 = Pop_operandos(f->p);

	f->p = Push_operandos(f->p,valor3->topo->operando,valor3->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor2->topo->operando,valor2->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->tipo_operando);
}

void dup2_x2_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);
	pilha_operandos *valor3 = Pop_operandos(f->p);
	pilha_operandos *valor4 = Pop_operandos(f->p);

	f->p = Push_operandos(f->p,valor4->topo->operando,valor4->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor3->topo->operando,valor3->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor2->topo->operando,valor2->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->tipo_operando);
}

void swap_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	f->p = Push_operandos(f->p,valor1->topo->operando,valor1->topo->tipo_operando);
	f->p = Push_operandos(f->p,valor2->topo->operando,valor2->topo->tipo_operando);
}

void iadd_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	pilha_operandos *valor3 = CriarPilha_operandos();

	// Se os tipos dos valores forem iguais, e se esse tipo for inteiro
	valor3 = Push_operandos(valor3,valor1->topo->operando+valor2->topo->operando,valor1->topo->tipo_operando);
	valor3->topo->tipo_operando = valor1->topo->tipo_operando;
	f->p = Push_operandos(f->p,valor3->topo->operando,valor3->topo->tipo_operando);

}

void ladd_impl(frame *f, u1 par1, u1 par2){

}

void fadd_impl(frame *f, u1 par1, u1 par2){

}

void dadd_impl(frame *f, u1 par1, u1 par2){

}


// Overflow pode ocorrer, mas mesmo assim, exceção não é lançada. Ou seja, é só subtrair
void isub_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	pilha_operandos *valor3 = CriarPilha_operandos();

	valor3 = Push_operandos(valor3,valor1->topo->operando-valor2->topo->operando, INTEGER_OP);
	valor3->topo->tipo_operando = valor1->topo->tipo_operando;
	f->p = Push_operandos(f->p,valor3->topo->operando,valor3->topo->tipo_operando);
}

void lsub_impl(frame *f, u1 par1, u1 par2){

}

void fsub_impl(frame *f, u1 par1, u1 par2){

}

void dsub_impl(frame *f, u1 par1, u1 par2){

}

void imul_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	pilha_operandos *valor3 = CriarPilha_operandos();

	valor3 = Push_operandos(valor3,valor1->topo->operando*valor2->topo->operando, INTEGER_OP);
	valor3->topo->tipo_operando = valor1->topo->tipo_operando;
	f->p = Push_operandos(f->p,valor3->topo->operando,valor3->topo->tipo_operando);
}

void lmul_impl(frame *f, u1 par1, u1 par2){

}

void fmul_impl(frame *f, u1 par1, u1 par2){

}

void dmul_impl(frame *f, u1 par1, u1 par2){

}



void idiv_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	pilha_operandos *valor3 = CriarPilha_operandos();
	if(valor2->topo->operando == 0){
		// Lançar exceção ArithmeticException
	}
	valor3 = Push_operandos(valor3,valor1->topo->operando/valor2->topo->operando, INTEGER_OP);
	valor3->topo->tipo_operando = valor1->topo->tipo_operando;

	f->p = Push_operandos(f->p,valor3->topo->operando,valor3->topo->tipo_operando);
}

void ldiv_impl(frame *f, u1 par1, u1 par2){

}

void fdiv_impl(frame *f, u1 par1, u1 par2){

}

void ddiv_impl(frame *f, u1 par1, u1 par2){

}

void irem_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	pilha_operandos *valor3 = CriarPilha_operandos();

	if(valor2->topo->operando == 0){
		// Lançar Arithmetic Exception
	}

	i4 valor_push = valor1->topo->operando - (valor1->topo->operando/valor2->topo->operando) * valor2->topo->operando;

	valor3 = Push_operandos(valor3,valor_push,valor1->topo->tipo_operando);
	valor3->topo->tipo_operando = valor1->topo->tipo_operando;

	f->p = Push_operandos(f->p,valor3->topo->operando,valor3->topo->tipo_operando);
}

void lrem_impl(frame *f, u1 par1, u1 par2){

}

void frem_impl(frame *f, u1 par1, u1 par2){

}

void drem_impl(frame *f, u1 par1, u1 par2){

}

void ineg_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);

	// Colocar o valor na pilha negado
	f->p = Push_operandos(f->p,-(valor1->topo->operando),valor1->topo->tipo_operando);
}

void lneg_impl(frame *f, u1 par1, u1 par2){

}

void fneg_impl(frame *f, u1 par1, u1 par2){

}

void dneg_impl(frame *f, u1 par1, u1 par2){

}

void ishl_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	i4 s = (valor2->topo->operando << 27) >> 27;

	i4 resultado = valor1->topo->operando << s;

	f->p = Push_operandos(f->p,resultado,valor1->topo->tipo_operando);
}

void lshl_impl(frame *f, u1 par1, u1 par2){

}


void ishr_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	i4 s = (i4) (valor2->topo->operando << 27) >> 27;

	i4 resultado = (i4) valor1->topo->operando >> s;

	f->p = Push_operandos(f->p,resultado,valor1->topo->tipo_operando);
}

void lshr_impl(frame *f, u1 par1, u1 par2){

}

// Verificar se a implementação é essa mesmo, para fazer a extensão do sinal
void iushr_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	u4 s = (u4) (valor2->topo->operando << 27) >> 27;

	u4 resultado = (u4) valor1->topo->operando >> s;

	f->p = Push_operandos(f->p,(i4) resultado,valor1->topo->tipo_operando);
}

void lushr_impl(frame *f, u1 par1, u1 par2){

}

void iand_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	i4 resultado = valor1->topo->operando & valor2->topo->operando;

	f->p = Push_operandos(f->p,resultado,valor1->topo->tipo_operando);
}

void land_impl(frame *f, u1 par1, u1 par2){

}

void ior_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	i4 resultado = valor1->topo->operando | valor2->topo->operando;

	f->p = Push_operandos(f->p,resultado,valor1->topo->tipo_operando);
}

void lor_impl(frame *f, u1 par1, u1 par2){

}

void ixor_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	i4 resultado = valor1->topo->operando ^ valor2->topo->operando;

	f->p = Push_operandos(f->p,resultado,valor1->topo->tipo_operando);
}

void lxor_impl(frame *f, u1 par1, u1 par2){

}

void iinc_impl(frame *f,u1 index, i1 constante){
	// Estender o sinal para 32 bits
	i4 inteiro_constante = (i4) constante;

	f->v[index].variavel += inteiro_constante;
}

void iinc_fantasma(frame *par0, u1 par1, u1 par2){

}

void i2l_impl(frame *f, u1 par1, u1 par2){

}

void i2f_impl(frame *f, u1 par1, u1 par2){

}

void i2d_impl(frame *f, u1 par1, u1 par2){

}

void l2i_impl(frame *f, u1 par1, u1 par2){

}

void l2f_impl(frame *f, u1 par1, u1 par2){

}

void l2d_impl(frame *f, u1 par1, u1 par2){

}

void f2i_impl(frame *f, u1 par1, u1 par2){

}

void f2l_impl(frame *f, u1 par1, u1 par2){

}

void f2d_impl(frame *f, u1 par1, u1 par2){

}

void d2i_impl(frame *f, u1 par1, u1 par2){

}

void d2l_impl(frame *f, u1 par1, u1 par2){

}

void d2f_impl(frame *f, u1 par1, u1 par2){

}

void i2b_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);

	i1 truncado = (i1) valor1->topo->operando;

	i4 resultado = (i4) truncado;

	f->p = Push_operandos(f->p,resultado,BYTE_OP);
}

void i2c_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);

	i1 truncado = (i1) valor1->topo->operando;

	i4 resultado = (i4) truncado;

	f->p = Push_operandos(f->p,resultado,CHAR_OP);
}

void i2s_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *valor1 = Pop_operandos(f->p);

	i2 truncado = (i2) valor1->topo->operando;

	i4 resultado = (i4) truncado;

	f->p = Push_operandos(f->p,resultado,SHORT_OP);
}

void lcmp_impl(frame *f, u1 par1, u1 par2){

}

void fcmpl_impl(frame *f, u1 par1, u1 par2){

}

void fcmpg_impl(frame *f, u1 par1, u1 par2){

}

void dcmpl_impl(frame *f, u1 par1, u1 par2){

}

void dcmpg_impl(frame *f, u1 par1, u1 par2){

}

void ifeq_impl(frame *f, u1 branchbyte1, u1 branchbyte2){

	
	pilha_operandos *valor = Pop_operandos(f->p);

	if(valor->topo->operando == 0){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
		// Alterar o PC aqui para fazer o branch
	}
}

void ifne_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor = Pop_operandos(f->p);

	if(valor->topo->operando !=0){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void iflt_impl(frame *f, u1 branchbyte1, u1 branchbyte2){

	pilha_operandos *valor = Pop_operandos(f->p);

	if(valor->topo->operando<0){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void ifge_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor = Pop_operandos(f->p);

	if(valor->topo->operando >= 0){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void ifgt_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor = Pop_operandos(f->p);

	if(valor->topo->operando > 0){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void ifle_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor = Pop_operandos(f->p);

	if(valor->topo->operando <= 0){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void if_icmpeq_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	if(valor1->topo->operando == valor2->topo->operando){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void if_icmpne_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	if(valor1->topo->operando != valor2->topo->operando){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void if_icmplt_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	if(valor1->topo->operando < valor2->topo->operando){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void if_icmpge_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	if(valor1->topo->operando >= valor2->topo->operando){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void if_icmpgt_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	if(valor1->topo->operando > valor2->topo->operando){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void if_icmple_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	if(valor1->topo->operando <= valor2->topo->operando){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void acmpeq_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	if(valor1->topo->operando == valor2->topo->operando){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void acmpne_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor1 = Pop_operandos(f->p);
	pilha_operandos *valor2 = Pop_operandos(f->p);

	if(valor1->topo->operando != valor2->topo->operando){
		u2 branchoffset = (branchbyte1 << 8) | branchbyte2;
	}
}

void inst_goto_impl(frame *f,u1 branchbyte1, u1 branchbyte2){
	u2 branchoffset = (branchbyte1 << 8) | branchbyte2;

	// Efetuar o branch com branch offset
}

void jsr_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	u2 branchoffset = (branchbyte1 << 8) | branchbyte2;

	// Efetuar o branch com branch offset
}

void ret_impl(frame *f,u1 index, u1 par){
	// u1 endereco_retorno = f->v[index]->variavel;

	// Escrever no registrador PC
}

void tableswitch_fantasma(frame *par0, u1 par1, u1 par2){

}

void lookupswitch_fantasma(frame *par0, u1 par1, u1 par2){

}

/***** O valor retornado é entre frames. Analisar como acessar a estrutura global *****/
void ireturn_impl(frame *f, u1 par1, u1 par2){
	// Analisar as condições do método que deve ser retornado

	pilha_operandos *valor = Pop_operandos(f->p);

	// Empilhar na pilha de operandos do frame do chamador
	jvm->frames->topo->prox->f->p = Push_operandos(jvm->frames->topo->prox->f->p,(i4)valor->topo->operando,valor->topo->tipo_operando);
}

void lreturn_impl(frame *f, u1 par1, u1 par2){

}

void freturn_impl(frame *f, u1 par1, u1 par2){

}

void dreturn_impl(frame *f, u1 par1, u1 par2){

}

void areturn_impl(frame *f, u1 par1, u1 par2){
	// Analisar mesmas coisas do ireturn
	pilha_operandos *valor = Pop_operandos(f->p);
}

void inst_return_impl(frame *f, u1 par1, u1 par2){

	printf("EXECUÇÃO RETURN\n\n");

	// Empilhar NULL na pilha de operandos do frame chamador, ou seja, o próximo frame na pilha
	jvm->frames->topo->prox->f->p = Push_operandos(jvm->frames->topo->prox->f->p,-1,-1);
}

void getstatic_impl(frame *f, u1 indexbyte1, u1 indexbyte2){

	u2 indice_cp = (indexbyte1 << 8) | indexbyte2;

	// Resolver o field
	// Fieldref campo = f->cp[indice_cp];

	f->p = Push_operandos(f->p,(i4) indice_cp,REFERENCE_OP);
}

void putstatic_impl(frame *f, u1 indexbyte1, u1 indexbyte2){
	u2 indice_cp = (indexbyte1 << 8) | indexbyte2;

	// Resolver o field

	// Fieldref campo = f->cp[indice_cp];
}

void getfield_impl(frame *f, u1 indexbyte1, u1 indexbyte2){
	pilha_operandos *objeto = Pop_operandos(f->p);

	u2 indice_cp = (indexbyte1 << 8) | indexbyte2;

	// Resolver o field

	// struct Fieldref campo = f->cp[indice_cp];
}

void putfield_impl(frame *f, u1 indexbyte1, u1 indexbyte2){
	u2 indice_cp = (indexbyte1 << 8) | indexbyte2;

	// Resolver o field 

	// struct Fieldref campo = f->cp[indice_cp];
}

void invokevirtual_impl(frame *f, u1 indexbyte1, u1 indexbyte2){
	u2 indice_cp = (indexbyte1 << 8) | indexbyte2;

	// struct Methodref metodo = f->cp[indice_cp];

	char *nomeClasse = decodificaNIeNT(f->cp,indice_cp,CLASS_INDEX);

	printf("%s\n",nomeClasse);

}

void invokespecial_impl(frame *f, u1 par1, u1 par2){

}

void invokestatic_impl(frame *f, u1 indexbyte1, u1 indexbyte2){

	u2 indice_cp = (indexbyte1 << 8) | indexbyte2;
	if(resolverMetodo(f->cp,indice_cp)){
		frame *f_novo = criarFrame(obterClasseDoMetodo(f->cp,indice_cp));
		jvm->frames = Push_frames(jvm->frames,f_novo);
		f_novo = transferePilhaVetor(f,f_novo);
		// printf("VALOR: %04x\n\n\n",f_novo->v[0].variavel[0]);
		for(int i=0;i<sizeof(f_novo->v)/sizeof(f_novo->v[0]);i++){
			printf("VARIÁVEL LOCAL: %04x\n",*(f_novo->v[i].variavel));
		}
	}

}

void invokeinterface_impl(frame *f, u1 par1, u1 par2){

}

void inst_new_impl(frame *f, u1 indexbyte1, u1 indexbyte2){
	u2 indice_cp = (indexbyte1 << 8) | indexbyte2;

	// Resolver a classe

	// Alocar memória

	// Colocar o ponteiro na pilha de operandos
}

void newarray_impl(frame *f, u1 atype, u1 par1){
	pilha_operandos *count = Pop_operandos(f->p);
	i4 countnum = count->topo->operando;

	void *endereco = NULL;
	i4 referencia = 0;

	if(count<0){
		// Lançar exceção
	}
	else{
		switch(atype){
			case T_BOOLEAN:
				endereco = (u1*) malloc((countnum+1)*sizeof(u1));
				referencia = (u1) *((u1*) endereco);
			break;
	
			case T_CHAR:
				endereco = (i2*) malloc((countnum+1)*sizeof(i2));
				referencia = (i2) *((i2*) endereco);
			break;
	
			case T_FLOAT:
				endereco = (u4*) malloc((countnum+1)*sizeof(u4));
				referencia = (u4) *((u4*) endereco);
			break;
	
			case T_DOUBLE:
				endereco = (u4*) malloc(2*(countnum+1)*sizeof(u4));
				referencia = (u4) *((u4*) endereco);
			break;
	
			case T_BYTE:
				endereco = (i1*) malloc((countnum+1)*sizeof(i1));
				referencia = (i1) *((i1*) endereco);
			break;
	
			case T_SHORT:
				endereco = (i2*) malloc((countnum+1)*sizeof(i2));
				referencia = (i2) *((i2*) endereco);
			break;
	
			case T_INT:
				endereco = (i4*) malloc((countnum+1)*sizeof(i4));
				referencia = (i4) *((i4*) endereco);
			break;
	
			case T_LONG:
				endereco = (i4*) malloc(2*(countnum+1)*sizeof(i4));
				referencia = (i4) *((i4*) endereco);
			break;
		}
	
		/*// Inicializar com os valores default
		for(void *p=endereco,i=0;i<=countnum;i++,p++){
			// Alocar com -INT_MAX para marcar o fim do array
			if(i==countnum){
				*p = -INT_MAX;
			}
			else{
				*p=0;
			}
		}*/
	
		f->p = Push_operandos(f->p,referencia,REFERENCE_OP);
	}
}

void anewarray_impl(frame *f, u1 par1, u1 par2){

}

void arraylength_impl(frame *f, u1 par1, u1 par2){
	pilha_operandos *array_ref = Pop_operandos(f->p);
	i4 referencia = array_ref->topo->operando;
	int tamanho = 0;

	/* Observação */
	// Não tem como descobrir o tipo do elemento, a princípio.
	// Como fazer esse incremento? Foi alocado como void, mas com sizeofs diferentes (observar instrução newarray)
	// O void vai garantir que o incremento é o mesmo?
	/*for (void *p = referencia;*p!=-INT_MAX;p++,tamanho++){
		
	}*/

	f->p = Push_operandos(f->p,tamanho,INTEGER_OP);

}

void athrow_impl(frame *f, u1 par1, u1 par2){

}

void checkcast_impl(frame *f, u1 par1, u1 par2){

}

void instanceof_impl(frame *f, u1 par1, u1 par2){

}

void monitorenter_impl(frame *f, u1 par1, u1 par2){

}

void monitorexit_impl(frame *f, u1 par1, u1 par2){

}

void wide_impl(frame *f, u1 par1, u1 par2){

}

void multianewarray_impl(frame *f, u1 par1, u1 par2){

}

void ifnull_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor = Pop_operandos(f->p);

	u2 offset = 0;

	if(valor==NULL){
		offset = (branchbyte1 << 8) | branchbyte2;
	}
	else{
		// Continuar execução normalmente
	}
}

void ifnonnull_impl(frame *f, u1 branchbyte1, u1 branchbyte2){
	pilha_operandos *valor = Pop_operandos(f->p);

	u2 offset = 0;

	if(valor!=NULL){
		offset = (branchbyte1 << 8) | branchbyte2;
	}
	else{
		// Continuar execução normalmente
	}
}

void goto_w_impl(frame *f, u1 par1, u1 par2){

}

void jsr_w_impl(frame *f, u1 par1, u1 par2){

}



























