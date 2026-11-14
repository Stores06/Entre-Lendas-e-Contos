#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//Dados:
int Dados (int valor) {
	int dado = 1 + (rand() % valor);
	return dado;
}


//LIMPEZA:

void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limparTela(void) {
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}	
//Criacao de personagem:

typedef struct {
	int PVMAX;
	int PVAtual;
	int agilidade;
	int forca;
	int PEMAX;
	int PEAtual;
	int defesa;
	int habilidade;
} Atributos;
typedef enum {
	COMBATENTE = 1,
	ESPECIALISTA,
	OCULTISTA
} tipoCLASSE;
typedef struct {
	Atributos atributos;
	bool ataqueEspecial;
	int bonusAtaqueEspecial;
} Combatente;
typedef struct {
	Atributos atributos;
	bool perito;
	int bonusPerito;
} Especialista;
typedef struct {
	Atributos atributos;
	bool tatuagens;
	int dadosRitual;
} Ocultista;

//Criacao de armas:

typedef struct {
	char nome[30];
	int quantDado;
	int tipoDado;
	int margemAmeaca;
	int multi;
} Arma;
Arma armas[6] = {
	{"Montante", 2, 6, 19, 2},
	{"Machado", 1, 8, 20, 3},
	{"Espada", 1, 10, 19, 2},
	{"Fuzil de assalto", 2, 10, 20, 2},
	{"Fuzil de Caca", 2, 8, 19, 3},
	{"Submetralhadora", 3, 6, 20, 3}
};
Arma escolherArma (Arma *a) {
	int escolha;
	do {
		limparTela();
		printf("Escolha um arma:\n");
		for (int i = 0; i < 6; i++) {
			printf("%d - %s\n", i+1, a[i].nome);
			printf("Dano: %dd%d\n", a[i].quantDado, a[i].tipoDado);
			printf("Margem de ameaca: %d\n", a[i].margemAmeaca);
			printf("Multiplicador de Crítico: x%d\n\n", a[i].multi);
		}
		if (scanf("%d", &escolha) != 1) {
			printf("Escolha invalida, tente novamente.\n");
			limparBuffer();
			escolha = 0;
		}
		else if ((escolha < 1) || (escolha > 6)) {
			printf("Opcao invalida! Tente novamente\n");
		} 
	} while ((escolha < 1) || (escolha > 6));
	return a[escolha - 1];
}


//Ficha do heroi:

typedef struct {
	tipoCLASSE classe;
	int XP;
	int nivel;
	Arma armaEquipada;
	union {
		Combatente combatente;
		Especialista especialista;
		Ocultista ocultista;
	} ficha;
} Heroi;
void levelUp (Heroi *p) {
	limparTela();
	if (p->nivel >= 5) {
		p->nivel = 5;
		return;
	}
	p->nivel += 1;
	if (p->nivel == 5) {
		printf("\n[SUBIU DE NIVEL!] Parabens, voce chegou ao nivel maximo\n");
	}
	else {
		printf("\n[SUBIU DE NIVEL!] Parabens! Voce subiu para o nivel %d!\n", p->nivel);
	}
	if (p->classe == COMBATENTE) {
		p->ficha.combatente.atributos.PVMAX += 13;
		p->ficha.combatente.atributos.PVAtual += 13;
		p->ficha.combatente.atributos.agilidade += 0;
		p->ficha.combatente.atributos.forca += 1;
		p->ficha.combatente.atributos.PEMAX += 2;
		p->ficha.combatente.atributos.PEAtual += 2;
		p->ficha.combatente.atributos.defesa += 4;
		if (p->nivel == 3) {
			p->ficha.combatente.bonusAtaqueEspecial = 10;
			printf("Sua habilidade [Ataque Especial] subiu para um bonus de +10\n");
		}
		else if (p->nivel == 5) {
			p->ficha.combatente.bonusAtaqueEspecial = 15;
			printf("Sua habilidade [Ataque Especial] subiu para um bonus de +15\n");
		}
	}
	else if (p->classe == ESPECIALISTA) {
		p->ficha.especialista.atributos.PVMAX += 7;
		p->ficha.especialista.atributos.PVAtual += 7;
		p->ficha.especialista.atributos.agilidade += 1;
		p->ficha.especialista.atributos.forca += 0;
		p->ficha.especialista.atributos.PEMAX += 5;
		p->ficha.especialista.atributos.PEAtual += 5;
		p->ficha.especialista.atributos.defesa += 2;
		if (p->nivel == 3) {
			p->ficha.especialista.bonusPerito = 8;
			printf("Sua habilidade [Perito] subiu para um bonus de +1d8\n");
		}
		else if (p-> nivel == 5) {
			p->ficha.especialista.bonusPerito = 10;
			printf("Sua habilidade [Perito] subiu para um bonus de +1d10\n");
		}
	}
	else if (p->classe == OCULTISTA) {
		p->ficha.ocultista.atributos.PVMAX += 4;
		p->ficha.ocultista.atributos.PVAtual += 4;
		p->ficha.ocultista.atributos.agilidade += 1;
		p->ficha.ocultista.atributos.forca += 0;
		p->ficha.ocultista.atributos.PEMAX += 8;
		p->ficha.ocultista.atributos.PEAtual += 8;
		p->ficha.ocultista.atributos.defesa += 1;
		if (p->nivel == 3) {
			p->ficha.ocultista.dadosRitual = 4;
			printf("O dano dos seus rituais aumentaram para 4d6\n");
		}
		else if (p->nivel == 5) {
			p->ficha.ocultista.dadosRitual = 5;
			printf("O dano dos seus rituais aumentaram para 5d6\n");
		}
	}
	printf("E recebeu um aumento em seus atributos!\n");
}
void ganhoXP (Heroi *p) {
	if (p->nivel == 5) {
		printf("Voce ja esta no nivel maximo, nao recebera mais XP.\n");
	}
	else {
		int xp = Dados(4);
		p->XP += xp;
		printf("Voce recebeu %d de XP", xp);
		while (p->XP >= 10) {
			p->XP -= 10;
			levelUp(p);
		}
	}	
}
int confirmarClasse(void) {
	int confirmClasse = 0;
	int CLASSE = 0;
	int escolha = 0;
	do {
		limparTela();
		printf("Escolha sua classe: \n\n");
		printf("1 - Combatente\n");
		printf("2 - Especialista\n");
		printf("3 - Ocultista\n");
		if (scanf("%d", &escolha) != 1) {
			printf("Escolha invalida, tente novamente.\n");
			limparBuffer();
			escolha = 0;
		}
		switch(escolha) {
			case 1:
				limparTela();
				printf("A classe Combatente e focada em ataques corpo a corpo, sendo a mais resistente e forte das 3, mas, em contra partida, e a que possui menos PE e tambem e a mais lenta. Sua habilidade especial e o Ataque especial, onde, no nivel 1, ao gastar 3PE recebe um bonus de +5 em testes de ataque e em dano, no nivel 3 o custo aumenta para 4PE e o bonus passa para +10 e no nivel 5 o custo aumenta para 5PE.\n\n");
				printf("Deseja jogar com essa classe?\n");
				printf("1 - Sim\n");
				printf("2 - Nao\n");
				if (scanf("%d", &confirmClasse) != 1) {
					printf("Escolha invalida, tente novamente.\n");
					limparBuffer();
					confirmClasse = 0;
				}
				if (confirmClasse == 1) {
					CLASSE = 1;
					printf("Voce escolheu a classe combatente.\n");
					break;
				}
				else if (confirmClasse == 2) {
					break;
				}
				else {
					printf("Opcao invalida, tente novamente.\n");
					continue;
				}
			case 2:
				limparTela();
				printf("A classe Especialista e focada em ataques a distancia com armas de disparo, sendo a classe mais rapida das 3, mas, em contra partida, os seus demais Status nao tem nenhum destaque, sendo mediano em todos. Sua habilidade especial e o Perito, onde, no nivel 1, ao gastar 3PE recebe um bonus de +1d6 em qualquer teste, não se aplica a rolagem de dano, no nivel 3 o custo aumenta para 4PE e o bonus para 1d8 e no nivel 5 o custo aumenta para 5PE e o bonus para 1d10, esse efeito dura apenas um turno.\n\n");
				printf("Deseja jogar com essa classe?\n");
				printf("1 - Sim\n");
				printf("2 - Nao\n");
				if (scanf("%d", &confirmClasse) != 1) {
					printf("Escolha invalida, tente novamente.\n");
					limparBuffer();
					confirmClasse = 0;
				}
				if (confirmClasse == 1) {
					CLASSE = 2;
					printf("Voce escolheu a classe especialista.\n");
					break;
				}
				else if (confirmClasse == 2) {
					break;
				}
				else {
					printf("Opcao invalida, tente novamente.\n");
					continue;
				}
			case 3:
				limparTela();
				printf("A classe Ocultista e focada em conjurar rituais tendo um custo de 2PE para atacar, causando 3d6 de dano direto pois os rituais tem acerto garantido, com sua quantidade de PE sendo a maior entre as classes, em contra partida, é a menos resistente entre as 3 e nao causa dano critico. Sua habilidade especial sao as tatuagens ritualisticas, onde, ao gastar 10PE para ativa-la, o custo para conjurar rituais e zerado pelo resto do combate. Essa habilidade nao evolui com o passar dos niveis, mas o dano dos seus rituais aumentam, no nivel 3 passa a ser 4d6 e no nivel 5 passa para 5d6.\n\n");
				printf("Deseja jogar com essa classe?\n");
				printf("1 - Sim\n");
				printf("2 - Nao\n");
				if (scanf("%d", &confirmClasse) != 1) {
					printf("Escolha invalida, tente novamente.\n");
					limparBuffer();
					confirmClasse = 0;
				}
				if (confirmClasse == 1) {
					CLASSE = 3;
					printf("Voce escolheu a classe ocultista.\n");
					break;
				}
				else if (confirmClasse == 2) {
					break;
				}
				else {
					printf("Opcao invalida, tente novamente.\n");
					continue;
				}
			default:
				printf("Opcao invalida, tente novamente\n");
				continue;
		}
	} while ((CLASSE < 1) || (CLASSE > 3));
	return CLASSE;
}

//Criacao de habilidades:

void habPerito (Heroi *p) {
	int custoPE;
	int tipoDado;
	if ((p->nivel >= 1) && (p->nivel < 3)) {
		custoPE = 3;
		tipoDado = 6;
	}
	else if ((p->nivel >= 3) && (p->nivel < 5)) {
		custoPE = 4;
		tipoDado = 8;
	}
	else if (p->nivel == 5) {
		custoPE = 5;
		tipoDado = 10;
	}
	if (p->ficha.especialista.atributos.PEAtual >= custoPE) {
		p->ficha.especialista.atributos.PEAtual -= custoPE;
		p->ficha.especialista.perito = true;
		p->ficha.especialista.bonusPerito = tipoDado;
		printf("\n[PERITO ATIVADO] -%d PE +1d%d\n", custoPE, tipoDado);
	}
	else {
		printf("Voce nao tem PE suficiente para usar essa habilidade!\n");
	}
}
void habAtaqueEspecial (Heroi *p) {
	int custoPE;
	int bonusAtaqEsp;
	if ((p->nivel >= 1) && (p->nivel < 3)) {
		custoPE = 3;
		bonusAtaqEsp = 5;
	}
	else if ((p->nivel >= 3) && (p->nivel < 5)) {
		custoPE = 4;
		bonusAtaqEsp = 10;
	}
	else if (p->nivel == 5) {
		custoPE = 5;
		bonusAtaqEsp = 15;
	}
	if (p->ficha.combatente.atributos.PEAtual >= custoPE) {
		p->ficha.combatente.atributos.PEAtual -= custoPE;
		p->ficha.combatente.ataqueEspecial = true;
		p->ficha.combatente.bonusAtaqueEspecial = bonusAtaqEsp;
		printf("\n[ATAQUE ESPECIAL ATIVADO] -%d PE +%d no seu proximo ataque\n", custoPE, bonusAtaqEsp);
	}
	else {
		printf("Voce nao tem PE suficiente para usar essa habilidade!\n");
	}
}
void habTatuagem (Heroi *p) {
	if (p->ficha.ocultista.atributos.PEAtual >= 10) {
		p->ficha.ocultista.atributos.PEAtual -= 10;
		p->ficha.ocultista.tatuagens = true;
		printf("\n[TATUAGENS RITUALISTICAS ATIVADAS] -10 PE, custo para conjurar rituais zerado pelo resto do combate\n");
	}
	else {
		printf("Voce nao tem PE suficiente para usar essa habilidade!\n");
	}
}
void finalizarTurno (Heroi *p) {
	if (p->classe == COMBATENTE) {
		p->ficha.combatente.ataqueEspecial = false;
	}
	else if (p->classe == ESPECIALISTA) {
		p->ficha.especialista.perito = false;
	}
}
void fimCombate (Heroi *p) {
	if (p->classe == OCULTISTA) {
		p->ficha.ocultista.tatuagens = false;
	}
	else if (p->classe == COMBATENTE) {
		p->ficha.combatente.ataqueEspecial = false;
	}
	else if (p->classe == ESPECIALISTA) {
		p->ficha.especialista.perito = false;
	}
}


//Criacao de mostros:

typedef struct {
	char nome[50];
	int PVMAX;
	int PVAtual;
	int defesa;
	int bonusAtaq;
	int quantDados;
	int tipoDado;
	int multi;
}Monstro;
Monstro monstros[9] = {
	//Fase 1:
	{"Zumbi de Sangue", 45, 45, 11, 5, 1, 6, 2},
	{"Esqueleto de lodo", 40, 40, 8, 5, 2, 6, 2},
	{"Existido", 36, 36, 7, 5, 1, 4, 2},
	//Fase 2:
	{"Aracnasita", 75, 75, 17, 11, 2, 10, 2},
	{"Ciborgue", 85, 85, 19, 10, 1, 10, 2},
	{"Zumbi de sangue bestial", 80, 80, 17, 11, 2, 10, 2},
	//Fase 3:
	{"Infecticidio", 120, 120, 21, 13, 3, 10, 2},
	{"Anarquico descontrolado", 105, 105, 22, 13, 2, 12, 2},
	{"Minotauro", 150, 150, 25, 17, 3, 10, 3}
};


//Combate:

Atributos *obterAtributos(Heroi *p) {
	switch (p->classe) {
		case COMBATENTE:
			return &p->ficha.combatente.atributos;
		case ESPECIALISTA:
			return &p->ficha.especialista.atributos;
		case OCULTISTA:
			return &p->ficha.ocultista.atributos;
		default:
			return NULL;
	}
}
int rolarDanoJog (Arma *a) {
	int dano = 0;
	for (int i = 0; i < a->quantDado; i++) {
		dano += Dados(a->tipoDado);
	}
	return dano;
}
void ataqueHeroi (Heroi *p, Monstro *m) {
	Atributos *a = obterAtributos(p);
	int dano = 0;
	if (p->classe == OCULTISTA) {
		if (p->ficha.ocultista.tatuagens) {
			for (int i = 0; i < p->ficha.ocultista.dadosRitual; i++) {
				dano += Dados(6);
			}
			m->PVAtual -= dano;
			if (m->PVAtual < 0) {
				m->PVAtual = 0;
			}
			printf("O dano causado foi de %d\n", dano);
		}
		else {
			if (a->PEAtual >= 2) {
				a->PEAtual -= 2;
				for (int i = 0; i < p->ficha.ocultista.dadosRitual; i++) {
					dano += Dados(6);
				}
				m->PVAtual -= dano;
				if (m->PVAtual < 0) {
					m->PVAtual = 0;
				}
				printf("O dano causado foi de %d\n", dano);
			}
			else {
				printf("Voce nao tem PE suficiente para atacar\n");
			}
		}
	}
	else {
		int dado = Dados(20);
		int teste = 0;
		int bonus = 0;
		bool critico = false;
		if (p->classe == COMBATENTE) {
			if (p->ficha.combatente.ataqueEspecial) {
				bonus += p->ficha.combatente.bonusAtaqueEspecial;
			}
		}
		else if (p->classe == ESPECIALISTA) {
			bonus += a->agilidade;
			if (p->ficha.especialista.perito) {
				bonus += Dados(p->ficha.especialista.bonusPerito);
			}
		}
		teste = dado + bonus;
		printf("Seu teste de ataque foi de %d\n", teste);
		if (teste > m->defesa) {
			dano += rolarDanoJog (&p->armaEquipada);
			if (p->classe == COMBATENTE) {
				dano += a->forca;
				if (p->ficha.combatente.ataqueEspecial) {
					dano += p->ficha.combatente.bonusAtaqueEspecial;
				}
			}
			if (dado >= p->armaEquipada.margemAmeaca) {
				dano *= p->armaEquipada.multi;
				critico = true;
			}
			m->PVAtual -= dano;
			if (m->PVAtual < 0){
				m->PVAtual = 0;
			}
			printf("\nVoce acertou!\n");
			if (critico) {
				printf("UM ACERTO CRITICO!\n");
			}
			printf("O dano causado foi de %d\n", dano);
		}
		else {
			printf("Voce errou o/a %s\n", m->nome);
		}
	}
	finalizarTurno(p);
}
void ataqueMonst (Heroi *p, Monstro *m) {
	Atributos *a = obterAtributos(p);
	int dado = Dados(20);
	int teste = dado + m->bonusAtaq;
	int dano = 0;
	printf("O/A %s te ataca!\n", m->nome);
	if (teste > a->defesa) {
		for (int i = 0; i < m->quantDados; i++) {
			dano += Dados(m->tipoDado);
		}
		if (dado == 20) {
			printf("FOI UM ACERTO CRITICO!!\n");
			dano *= m->multi;
		}
		a->PVAtual -= dano;
		if (a->PVAtual < 0) {
			a->PVAtual = 0;
		}
		printf("O/A %s te acerta e voce recebe %d de dano.\n",m->nome, dano);
	}
	else {
		printf("Mas voce consegue evitar o ataque.\n");
	}
	printf("Seu PV: %d:%d\n", a->PVAtual, a->PVMAX);
}

void Combate (Heroi *p, Monstro *m) {
	int escolha = 0;
	int teste;
	int DTFuga;
	bool combat = true;
	Atributos *a = obterAtributos(p);
	printf("Um(a) %s aparece na sua frente e parte em sua direcao.\n", m->nome);
	do{
		printf("O que voce faz? \n");
		printf("1 - Ataque\n");
		printf("2 - Habilidade\n");
		printf("3 - Status\n");
		printf("4 - Tomar folego\n");
		printf("5 - Fugir\n");
		printf("Escolha: ");
		if (scanf("%d", &escolha) != 1) {
			printf("Escolha invalida, tente novamente.\n");
			limparBuffer();
			escolha = 0;
		}
		switch (escolha) {
			case 1:
				limparTela();
				ataqueHeroi(p, m);
				if (m->PVAtual > 0) {
					ataqueMonst (p,m);
				}
				break;
			case 2:
				limparTela();
				if (p->classe == COMBATENTE) {
					habAtaqueEspecial (p);
				}
				else if (p->classe == ESPECIALISTA) {
					habPerito (p);
				}
				else if (p->classe == OCULTISTA) {
					habTatuagem (p);
				}
				break;
			case 3:
				limparTela();
				if (p->classe == COMBATENTE || p->classe == ESPECIALISTA) {
					printf("-----STATUS-----\n");
					printf("PV: %d:%d\n", a->PVAtual, a->PVMAX);
					printf("PE: %d:%d\n", a->PEAtual, a->PEMAX);
					printf("Defesa: %d\n", a->defesa);
					printf("Arma: %s\n", p->armaEquipada.nome);
				}
				else {
					printf("-----STATUS-----\n");
					printf("PV: %d:%d\n", a->PVAtual, a->PVMAX);
					printf("PE: %d:%d\n", a->PEAtual, a->PEMAX);
					printf("Defesa: %d\n", a->defesa);
				}
				break;
			case 4:
				limparTela();
				a->PEAtual += Dados(6);
				if (a->PEAtual > a->PEMAX) {
					a->PEAtual = a->PEMAX;
				}
				printf("Voce toma um ar e descansa um pouco o seu corpo recuperando um pouco de PE.\n");
				printf("A criatura, vendo essa brecha, te ataca.\n");
				ataqueMonst (p,m);
				break;
			case 5:
				limparTela();
				teste = 0;
				if (p->classe == ESPECIALISTA) {
					if (p->ficha.especialista.perito) {
						int testePerito = Dados(p->ficha.especialista.bonusPerito);
						teste = testePerito;
					}
				}
				teste += Dados(20) + a->agilidade;
				DTFuga = Dados(20);
				if (teste >= DTFuga) {
					printf("Voce foge de %s.\n", m->nome);
					combat = false;
					fimCombate(p);
				}
				else if (teste < DTFuga) {
					printf("Voce nao consegue fugir e o %s te ataca.\n", m->nome);
					ataqueMonst (p,m);
				}
				break;
			default:
				limparTela();
				printf("Escolha invalida, tente novamente");
				break;
				
		}
		if (m->PVAtual <= 0) {
			printf("Voce derrotou o %s\n", m->nome);
			ganhoXP(p);
			fimCombate(p);
			combat = false;
		}
		else if (a->PVAtual <= 0) {
			printf("Voce foi derrotado por %s\n", m->nome);
			fimCombate(p);
			combat = false;
		}
	} while (combat == true);
}


//Salas:

typedef enum {
	VAZIA = 0,
	CURA,
	RECOMPENSA1,
	RECOMPENSA2,
	RECOMPENSA3,
	COMBATE1,
	COMBATE2,
	COMBATE3,
	COMBATE4,
	COMBATE5,
	COMBATE6,
	COMBATE7,
	COMBATE8,
	COMBATE9,
	PASSAGEM1,
	PASSAGEM2
} tipoSala;
void salaCura (Heroi *p) {
	limparTela();
	Atributos *a = obterAtributos(p);
	printf("Voce encontra uma sala em que se sente seguro para descansar.\n");
	for (int i = 0; i < 2; i++) {
		a->PVAtual += Dados(10);
		a->PEAtual += Dados(10);
	}
	if(a->PVAtual > a->PVMAX) {
		a->PVAtual = a->PVMAX;
	}
	if(a->PEAtual > a->PEMAX) {
		a->PEAtual = a->PEMAX;
	}
	printf("Voce recuperou uma parte de seus PV e PE.\n");
}
void salaRecompensa1 (Heroi *p) {
	limparTela();
	printf("Durante a exploracao do primeiro andar, voce encontra uma sala que possui relatórios sobre o paranormal e ganha XP.\n");
	ganhoXP(p);
}
void salaRecompensa2 (Heroi *p, Arma *a) {
	limparTela();
	if (p->classe == OCULTISTA) {
		printf("Voce encontra algumas escrituras sobre o paranormal e ganha XP.\n");
		ganhoXP(p);
	}
	else {
		printf("Ao explorar uma sala do segundo andar, voce encontra uma modificacao para o/a seu/sua %s.\n", a->nome);
		a->quantDado += 1;
		printf("O dano do/a seu/sua %s subiu de %dd%d para %dd%d.\n", a->nome, a->quantDado - 1, a->tipoDado, a->quantDado, a->tipoDado);
	}
}
void salaRecompensa3 (Heroi *p, Arma *a) {
	limparTela();
	if (p->classe == OCULTISTA) {
		printf("Voce encontra alguns selos de rituais e ganha XP.\n");
		ganhoXP(p);
	}
	else {
		printf("Ao adentrar em uma sala do terceiro andar, voce se depara com uma modificacao para o/a seu/sua %s.\n", a->nome);
		a->margemAmeaca -= 1;
		a->multi += 1;
		printf("A margem de ameca do/a seu/sua %s passou de %d para %d e o multiplicador de critico de %d para %d.\n", a->nome, a->margemAmeaca - 1, a->margemAmeaca, a->multi - 1, a->multi);
	}
}
void visitarSalas (int *fase, int posicao, Heroi *p, bool *passagemLib) {
	limparTela();
	switch (fase[posicao]) {
		case VAZIA: 
			printf("Voce encontra uma sala vazia.\n");
			break;
		case CURA:
			salaCura(p);
			fase[posicao] = VAZIA;
			break;
		case RECOMPENSA1:
			salaRecompensa1(p);
			fase[posicao] = VAZIA;
			break;
		case RECOMPENSA2:
			salaRecompensa2(p, &p->armaEquipada);
			fase[posicao] = VAZIA;
			break;
		case RECOMPENSA3:
			salaRecompensa3(p, &p->armaEquipada);
			fase[posicao] = VAZIA;
			break;
		case COMBATE1: {
			Monstro criatura = monstros[0];
			Combate(p, &criatura);
			if (criatura.PVAtual == 0) {
				fase[posicao] = VAZIA;
			}
			break;
		}
		case COMBATE2: {
			Monstro criatura = monstros[1];
			Combate(p, &criatura);
			if (criatura.PVAtual == 0) {
				fase[posicao] = VAZIA;
			}
			break;
		}
		case COMBATE3: {
			Monstro criatura = monstros[2];
			Combate(p, &criatura);
			if (criatura.PVAtual == 0) {
				fase[posicao] = VAZIA;
			}
			break;
		}
		case COMBATE4: {
			Monstro criatura = monstros[3];
			Combate(p, &criatura);
			if (criatura.PVAtual == 0) {
				fase[posicao] = VAZIA;
			}
			break;
		}
		case COMBATE5: {
			Monstro criatura = monstros[4];
			Combate(p, &criatura);
			if (criatura.PVAtual == 0) {
				fase[posicao] = VAZIA;
			}
			break;
		}
		case COMBATE6: {
			Monstro criatura = monstros[5];
			Combate(p, &criatura);
			if (criatura.PVAtual == 0) {
				fase[posicao] = VAZIA;
			}
			break;
		}
		case COMBATE7: {
			Monstro criatura = monstros[6];
			Combate(p, &criatura);
			if (criatura.PVAtual == 0) {
				fase[posicao] = VAZIA;
			}
			break;
		}
		case COMBATE8: {
			Monstro criatura = monstros[7];
			Combate(p, &criatura);
			if (criatura.PVAtual == 0) {
				fase[posicao] = VAZIA;
			}
			break;
		}
		case COMBATE9: {
			Monstro criatura = monstros[8];
			Combate(p, &criatura);
			if (criatura.PVAtual == 0) {
				fase[posicao] = VAZIA;
			}
			break;
		}
		case PASSAGEM1:
			printf("Voce encontra um cartao que da acesso ao proximo andar.\n");
			*passagemLib = true;
			fase[posicao] = VAZIA;
			break;
		case PASSAGEM2:
			printf("Voce encontra um arquivos onde está escrito o código para o proximo andar.\n");
			*passagemLib = true;
			fase[posicao] = VAZIA;
			break;		
	}
}
void explorarFase1 (Heroi *p) {
	int fase1[12] = {
		VAZIA, VAZIA, COMBATE1, VAZIA, RECOMPENSA1, VAZIA,
		COMBATE2, VAZIA, PASSAGEM1, VAZIA, COMBATE3, VAZIA
	};
	int mov, posicao = 0;
	bool passagemLib = false;
	Atributos *a = obterAtributos(p);
	printf("\n------PRIMEIRO ANDAR------\n");
	printf("OBJETIVO: Encontrar o cartao de acesso para o proximo andar\n");
	while (!passagemLib && a->PVAtual > 0) {
		limparBuffer();
		limparTela();
		printf("Precione <ENTER> para se movimentar\n");
		getchar();
		mov = Dados(6);
		posicao += mov;
		if (posicao >= 11) {
			posicao = 11;
			if (passagemLib == false) {
				printf("Voce encontra o elevador para o próximo andar, mas ele exige um cartao de acesso que voce nao possui.\n");
				printf("Voce decide voltar para a primeira sala para procurar de novo.\n");
				posicao = 0;
				continue;
			}
		}
		printf("Voce avancou %d salas.\n", mov);
		printf("Posicao atual: %d.\n", posicao + 1);
		visitarSalas(fase1, posicao, p, &passagemLib);
	}
}
void explorarFase2 (Heroi *p) {
	int fase2[12] = {
		VAZIA, VAZIA, CURA, RECOMPENSA2, VAZIA, COMBATE4,
		PASSAGEM2, COMBATE5, VAZIA, COMBATE6, VAZIA, VAZIA
	};
	int mov, posicao = 0;
	bool passagemLib = false;
	Atributos *a = obterAtributos(p);
	printf("\n------SEGUNDO ANDAR------\n");
	printf("OBJETIVO: Encontre o codigo de acesso para o proximo andar.\n");
	while (!passagemLib && a->PVAtual > 0) {
		limparBuffer();
		limparTela();
		printf("Precione <ENTER> para se movimentar\n");
		getchar();
		mov = Dados(6);
		posicao += mov;
		if (posicao >= 11) {
			posicao = 11;
			if (passagemLib == false) {
				printf("Voce encontra outro elevador, mas não entende o por que deles precisarem de dois, porem precisa de um codigo de acesso para usar esse elevador.\n");
				printf("Derrotado pelo elevador, voce retorna a primeira sala para procurar o codigo.\n");
				posicao = 0;
				continue;
			}
		}
		printf("Voce avancou %d salas.\n", mov);
		printf("Posicao atual: %d.\n", posicao + 1);
		visitarSalas(fase2, posicao, p, &passagemLib);
	}
}
void explorarFase3 (Heroi *p) {
	int fase3[12] = {
		VAZIA, VAZIA, RECOMPENSA3, VAZIA, COMBATE7, VAZIA,
		VAZIA, CURA, VAZIA, COMBATE8, VAZIA, COMBATE9
	};
	int mov, posicao = 0;
	bool derrotarBoss = false;
	Atributos *a = obterAtributos(p);
	printf("\n------TERCEIRO ANDAR------\n");
	printf("OBJETIVO: Derrote o minotauro no fim do terceiro andar.\n");
	while (!derrotarBoss && a->PVAtual > 0) {
		limparBuffer();
		limparTela();
		printf("Precione <ENTER> para se movimentar\n");
		getchar();
		mov = Dados(6);
		posicao += mov;
		if (posicao >= 11) {
			posicao = 11;
		}
		printf("Voce avancou %d salas.\n", mov);
		printf("Posicao atual: %d.\n", posicao + 1);
		if (fase3[posicao] == COMBATE9) {
			Monstro boss = monstros[8];
			Combate(p, & boss);
			if (boss.PVAtual <= 0) {
				derrotarBoss = true;
				fase3[posicao] = VAZIA;
			}
			else if (a->PVAtual > 0) {
				printf("Voce foge do minotauro e decide tentar ver o que tem nas outras salas antes de ir enfrenta-lo novamente.\n");
				posicao = 0;
				continue;
			}
		}
		else {
			bool passagemLib = false;
			visitarSalas (fase3, posicao, p, &passagemLib);
		}
	}
	if (derrotarBoss == true) {
		printf("PARABENS!!! Voce derrotou o minotauro e completou o jogo!\n");
	}
}


//JOGO:

int main () {
	srand((unsigned)time(NULL));
	Heroi heroi;
	heroi.classe = confirmarClasse();
	heroi.nivel = 1;
	heroi.XP = 0;
	if (heroi.classe == 1) {
		heroi.ficha.combatente.atributos.PVMAX = 41;
		heroi.ficha.combatente.atributos.PVAtual = 41;
		heroi.ficha.combatente.atributos.agilidade = 1;
		heroi.ficha.combatente.atributos.forca = 3;
		heroi.ficha.combatente.atributos.PEMAX = 13;
		heroi.ficha.combatente.atributos.PEAtual = 13;
		heroi.ficha.combatente.atributos.defesa = 16;
		heroi.ficha.combatente.ataqueEspecial = false;
		heroi.ficha.combatente.bonusAtaqueEspecial = 5;
		heroi.armaEquipada = escolherArma(armas);
	}
	else if (heroi.classe == 2) {
		heroi.ficha.especialista.atributos.PVMAX = 29;
		heroi.ficha.especialista.atributos.PVAtual = 29;
		heroi.ficha.especialista.atributos.agilidade = 3;
		heroi.ficha.especialista.atributos.forca = 2;
		heroi.ficha.especialista.atributos.PEMAX = 16;
		heroi.ficha.especialista.atributos.PEAtual = 16;
		heroi.ficha.especialista.atributos.defesa = 14;
		heroi.ficha.especialista.perito = false;
		heroi.ficha.especialista.bonusPerito = 6;
		heroi.armaEquipada = escolherArma(armas);
	}
	else if (heroi.classe == 3) {
		heroi.ficha.ocultista.atributos.PVMAX = 21;
		heroi.ficha.ocultista.atributos.PVAtual = 21;
		heroi.ficha.ocultista.atributos.agilidade = 2;
		heroi.ficha.ocultista.atributos.forca = 1;
		heroi.ficha.ocultista.atributos.PEMAX = 36;
		heroi.ficha.ocultista.atributos.PEAtual = 36;
		heroi.ficha.ocultista.atributos.defesa = 12;
		heroi.ficha.ocultista.tatuagens = false;
		heroi.ficha.ocultista.dadosRitual = 3;
	}
	Atributos *a = obterAtributos(&heroi);
	limparTela();
	printf("Voce chega em frente a uma instalacao de uma organizacao de cultistas, voce adentra sem pensar duas vezes. O ar gelado de dentro o/a atinge como se fosse uma pancada em seu rosto, mas segue em frente.\n");
	explorarFase1 (&heroi);
	if (a->PVAtual <= 0) {
		printf("No primeiro andar, serio isso?\n");
		return 0;
	}
	limparTela();
	printf("Ao descer o elevador, voce ouve um grunido abafado que aumenta quanto mais o elevador desce. Voce esta perto.\n");
	explorarFase2 (&heroi);
	if (a->PVAtual <= 0) {
		printf("Voce se bem, mas ainda nao foi o suficiente.\n");
		return 0;
	}
	limparTela();
	printf("Quando voce desce para o terceiro andar, avista mais um monte de salas, voce solta um suspiro desacreditado e aquele rugido esta muito mais perto.\n");
	explorarFase3 (&heroi);
	if (a->PVAtual <= 0) {
		printf("Voce se saiu melhor do que eu esperava, orgulhe-se, voce ate que e bem fortinho.\n");
		return 0;
	}
	return 0;
}
