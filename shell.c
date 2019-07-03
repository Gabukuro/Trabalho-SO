//Para compilar no terminal: gcc my-shell.c -o exe -lreadline && ./exe
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/readline.h> 
#include<readline/history.h>
#include <locale.h>
  
/* limpa a tela */
#define CLEAR() printf("\033[H\033[J")

void diretorio() {
	char cwd[1024];
	// Identifica o caminho do diretório atual
	getcwd(cwd, sizeof(cwd));
	printf("\nDiretório atual: %s\n\n", cwd); 
}


int linha(char* comando) {
	char* linha, *usuario;

	// Solicita um comando e receb o que o usuário digitar
	linha = readline(">> ");
	// Adciona no histórico o comando para ao clicar na seta pra cima seja possível a visualização
    add_history(linha);
    // Salva o comando digitado na variável passada por ponteiro comando
	strcpy(comando, linha);
}

void formataComando(char* comando, char** comandoFormatado) {
	int i;

	for (i = 0; i < 100; i++) { 
		// strsep para separar todas as palavras digitadas no comando
		comandoFormatado[i] = strsep(&comando, " ");

		if (comandoFormatado[i] == NULL)
			break;
		if (strlen(comandoFormatado[i]) == 0)
			i--;
	}
}

void help() {
	printf("\n** Parece que você precisa de ajuda **"
		"\nLista de comandos:"
		"\n- cd: muda de pasta"
		"\n- exit: sai do programa"
		"\n- ls: lista de pastas"
		"\n- hello: saudações"
		"\n\n");
}

void procuraComando(char** comando) {
    if(strcmp(comando[0], "exit") == 0) { // Compara o que foi digitado com "exit"
        printf("\nAté mais\n"); 
		exit(0);
    }
    else if(strcmp(comando[0], "help") == 0) { // Compara o que foi digitado com "help"
        help();
    }
    else if(strcmp(comando[0], "hello") == 0) { // Compara o que foi digitado com "hello"
		char* user;
        user = getenv("USER");
        printf("\nOlá %s, como vai você?\n\n", user);
	}
	else if(strcmp(comando[0], "cd") == 0) { // Compara o que foi digitado com "cd"
		chdir(comando[1]);
	}
    else { // Se o comando não exite na nossa shell, tenta execular pelo linux
        system(comando[0]);
    }
} 

int leComando(char* comando, char** comandoFormatado) { 
	formataComando(comando, comandoFormatado); // Separa todas as palavras digitadas
	procuraComando(comandoFormatado); // Procura o comando digitado
}

void inicio(){
	printf("\n============================"
		   "\n============================"
		   "\n\n\tBem vindo!"
		   "\n\n============================"
		   "\n============================\n");
	sleep(2);
}

int main() {
	char comando[100], *comandoFormatado[100];

    CLEAR();
    inicio();
	CLEAR();

	while(1) { // Loop infinito
        linha(comando); // Mostra a linha
		leComando(comando, comandoFormatado); // Recebe o comando
	}
}