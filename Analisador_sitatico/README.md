## **O Analisador Sintático**
    - Mateus Satos Messias 12548000
    - Pedro Borges Gudin 12547997

### 1. **Gramática da linguagem PL/0**
```
<programa> ::= <bloco> .
<bloco> ::= <declaracao> <comando>
<declaracao> ::= <constante> <variavel> <procedimento>
<constante> ::= CONST ident = numero <mais_const> ; | λ
<mais_const> ::= , ident = numero <mais_const> | λ
<variavel> ::= VAR ident <mais_var> ; | λ
<mais_var> ::= , ident <mais_var> | λ
<procedimento> ::= PROCEDURE ident ; <bloco> ; <procedimento> | λ
<comando> ::= ident := <expressao>
| CALL ident
| BEGIN <comando> <mais_cmd> END
| IF <condicao> THEN <comando>
| WHILE <condicao> DO <comando>
| λ
<mais_cmd> ::= ; <comando> <mais_cmd> | λ
<expressao> ::= <operador_unario> <termo> <mais_termos>
<operador_unario> ::= - | + | λ
<termo> ::= <fator> <mais_fatores>
<mais_termos> ::= - <termo> <mais_termos> | + <termo> <mais_termos> | λ
<fator> ::= ident | numero | ( <expressão> )
<mais_fatores> ::= * <fator> <mais_fatores> | / <fator> <mais_fatores> | λ
<condicao> ::= ODD <expressao>
| <expressao> <relacional> <expressao>
<relacional> ::= = | <> | < | <= | > | >=
```

Além disso:
* comentários são de única linha, entre chaves { }
* identificadores são formados por letras e dígitos, começando por letra
* só há números inteiros, formados por um ou mais dígitos (entre 0 e 9)

### 2. **Esquema da Gramática**
```mermaid
    graph LR;

    programa --> bloco --> ponto((.))

    subgraph bloco
        direction LR
        declaracao --> comando
    end
```
```mermaid
    graph LR;

    subgraph declaracao
        direction LR
        constante --> variavel --> procedimento
    end
```
```mermaid
    graph LR;

    subgraph constante
        direction LR
        const((CONST)) --> ident((ident)) --> igual((=)) --> numero((numero)) --> mais_const --> ponto_virg((;))
        lambda(("λ"))
    end

    subgraph mais_const
        direction LR
        virgula((,)) --> ident2((ident)) --> igual2((=)) --> numero2((numero)) --> mais_const2[mais_const] 
        lambda(("λ"))
    end
```
```mermaid
    graph LR;

    subgraph variavel
        direction LR
        var((VAR)) --> ident3((ident)) --> mais_var --> ponto_virg2((;))
        lambda2(("λ"))
    end

    subgraph mais_var
        direction LR
        virgula2((,)) --> ident4((ident)) --> mais_var2[mais_var] 
        lambda3(("λ"))
    end
```
```mermaid
    graph LR;

    subgraph procedimento
        direction LR
        proc((PROCEDURE)) --> ident5((ident)) --> ponto_virg3((;)) --> blocoo --> ponto_virg4((;)) --> procedimento2[procedimento]
        lambda4(("λ"))
    end
```
```mermaid
    graph LR;

    subgraph comando
        direction LR
        ident6((ident)) --> expressao
        call((CALL)) --> ident7((ident))
        begin((BEGIN)) --> comando2[comando] --> mais_cmd --> fim(END)
        se((IF)) --> condicao --> entao((THEN)) --> comando3[comando]
        enquanto((WHILE)) --> condicao2[condicao] --> faca((DO)) --> comando4[comando]
        lambda5(("λ"))
    end

    subgraph mais_cmd
        direction LR
        ponto_virg5((;)) --> comando5[comando] --> mais_cmd2[mais_cmd]
        lambda6(("λ"))
    end
```
```mermaid
    graph LR;

    subgraph expressao
        direction LR
        operador_unario --> termo --> mais_termos
    end

    subgraph operador_unario
        direction LR
        menos(("-"))
        mais(("+"))
        lambda7(("λ"))
    end

    subgraph termo
        direction LR
        fator --> mais_fatores
    end

    subgraph mais_termos
        direction LR
        menos2(("-")) --> termo2[termo] --> mais_termos2[mais_termos]
        mais2(("+")) --> termo3[termo] --> mais_termos3[mais_termos]
        lambda8(("λ"))
    end
```
```mermaid
    graph LR;

    subgraph fator
        direction LR
        ident8((ident))
        numero3((numero))
        abre_par(("(")) --> expressao2[expressao] --> fecha_par((")"))
    end
```
```mermaid
    graph LR;

    subgraph mais_fatores
        direction LR
        asterisco(("*")) --> fator2[fator] --> mais_fatores2[mais_fatores]
        barra(("/")) --> fator3[fator] --> mais_fatores3[mais_fatores]
        lambda9(("λ"))
    end
```
```mermaid
    graph LR;

    subgraph condicao
        direction LR
        odd(("ODD")) --> expressao3[expressao]
        expressao4[expressao] --> relacional --> expressao5[expressao]
    end

    subgraph relacional
        direction LR
        igual3(("="))
        difer(("<>"))
        menor(("<"))
        menorigual(("<="))
        maior((">"))
        maiorigual((">="))
    end
```
Baseado-se na gramática, os tokens podem incluir:
    
- **Palavras-reservadas**: `CONST`, `VAR`, `PROCEDURE`, `CALL`, `BEGIN`, `END`, `IF`, `THEN`, `WHILE`, `DO`, `ODD`
- **Identificadores**: Sequência de letras e dígitos, começando por letra.
- **Números inteiros**: Sequência de um ou mais dígitos.
- **Operadores**: `+`, `-`, `*`, `/`, `=`, `<>`, `<`, `<=`, `>`, `>=`
- **Símboloes especiais**: `:=`, `;`
- **Delimitadores**: `(`, `)`, `,`, `.`
- **Comentários**: `{` até `}` (ignorar o conteúdo)

### 2.1. **Automato para identificadores ou palavras-reservadas**
![Nao encotrou a imagem identificador_ou_palavra_reservada.png](imagens/identificador_ou_palavra_reservada.png)
### 2.2. **Automato para os números inteiros**
![Nao encotrou a imagem numero.png](imagens/numeros.png)
### 2.3. **Automato para os operadores aritimeticos**
![Nao encotrou a imagem operadores_aritimeticos.png](imagens/operadores_aritimeticos.png)
### 2.4. **Automato para os operadores relacionais**
![Nao encotrou a imagem operadores_relacionais.png](imagens/operadores_relacionais.png)
### 2.5. **Automato para os simbolos especiais e delimitadores**
![Nao encotrou a imagem simbolos_especiais_e_delimitadores.png](imagens/simbolos_especiais_e_delimitadores.png)
### 2.6. **Automato para os comentários**
![Nao encotrou a imagem comentario.png](imagens/comentario.png)
### 2.7. **Automato final**
![Nao encotrou a imagem final.png](imagens/final.png)

### 3. **Tabela de estados do automato**
| Estado | Letra | Número | +  | -  | *  | /  | <  | >  | =  | (  | )  | ;  | :  | ,  | .  | {  | }  | \n | \t | Espaço | Outro |
|--------|-------|--------|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|--------|-------|
| q0     | q1    | q2     | f3 | f4 | f5 | f6 | q3 | q4 | f7 | f16| f17| f14| q5 | f19| f15| q6 | e1 | q0 | q0 | q0     | e1    |
| q1     | q1    | q1     | f1 | f1 | f1 | f1 | f1 | f1 | f1 | f1 | f1 | f1 | f1 | f1 | f1 | f1 | f1 | f1 | f1 | f1     | f1    |
| q2     | e1    | q2     | f2 | f2 | f2 | f2 | f2 | f2 | f2 | f2 | f2 | f2 | f2 | f2 | f2 | f2 | f2 | f2 | f2 | f2     | f2    |
| q3     | f10   | f10    | f10| f10| f10| f10| f10| f8 | f9 | f10| f10| f10| f10| f10| f10| f10| f10| f10| f10| f10    | f10   |
| q4     | f12   | f12    | f12| f12| f12| f12| f12| f12| f11| f12| f12| f12| f12| f12| f12| f12| f12| f12| f12| f12    | f12   |
| q5     | e1    | e1     | e1 | e1 | e1 | e1 | e1 | e1 | f13| e1 | e1 | e1 | e1 | e1 | e1 | e1 | e1 | e1 | e1 | e1     | e1    |
| q6     | q6    | q6     | q6 | q6 | q6 | q6 | q6 | q6 | q6 | q6 | q6 | q6 | q6 | q6 | q6 | q6 | q0 | e2 | q6 | q6     | q6    |


## **Rodando e Compilando o programa**
### 1. **Requisitos de sistema**
Sistema utilizado --> Linux Ubuntu 22.04
                                                                                    
### 2. **Como rodar o programa**
- Para compilar o programa digite `make` ou `make all` no terminal
- Para rodar basta digitar `make run ARGS=<nome_do_programa_de_entrada.txt>`,
ja existe um programa teste na pasta que utilizaremos, portanto o comando para rodar fica:
 `make run ARGS=teste.txt`.

#### 2.1 **Saída do programa**
Ao rodar o programa com um arquivo de entrada será gerado um arquivo de saida
chamado `saida.txt` que contem os tokens gerados pelo analizador lexico.

