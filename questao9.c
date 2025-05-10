/*

Questão 9 – Primeira prova  
Matéria: Matemática Discreta 2  
Professora: Cristiane Loesch  
Aluno: Lucas Gabriel Gomes Aguiar  
Matrícula: 232004506  

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int verifica_primo(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int calcular_mdc(int a, int b) {
    int r = a % b;
    if (r == 0) return b;
    return calcular_mdc(b, r);
}

int inverso_modular(int G, int n) {
    int t = 0, novo_t = 1;
    int r = n, novo_r = G;
    while (novo_r != 0) {
        int quociente = r / novo_r;
        int temp = t;
        t = novo_t;
        novo_t = temp - quociente * novo_t;

        temp = r;
        r = novo_r;
        novo_r = temp - quociente * novo_r;
    }
    if (r > 1) return -1;
    if (t < 0) t += n;
    return t;
}

int calcular_base(int H, int G , int n) {
    if (calcular_mdc(G, n) != 1) {
        printf("O inverso modular de %d modulo %d nao existe (G e n nao sao primos entre si).\n", G, n);
        return -1;
    }

    int inverso = inverso_modular(G, n);
    if (inverso == -1) {
        printf("Erro ao calcular o inverso modular.\n");
        return -1;
    }

    int resultado = (H * inverso) % n;
    if (resultado < 0) resultado += n;
    return resultado;
}

int phi(int n) {
    int resultado = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            resultado -= resultado / i;
        }
    }
    if (n > 1)
        resultado -= resultado / n;
    return resultado;
}

int potencia_modular(int base, int expoente, int mod) {
    int resultado = 1;
    base %= mod;
    while (expoente > 0) {
        if (expoente % 2 == 1)
            resultado = (resultado * base) % mod;
        base = (base * base) % mod;
        expoente /= 2;
    }
    return resultado;
}

int resolver_congruencia(int a, int x, int n1) {
    int x1 = verifica_primo(n1) ? n1 - 1 : phi(n1);
    printf("x1 = %d\n", x1);

    int q = x / x1;
    int r = x % x1;
    printf("x = x1 * q + r = %d * %d + %d\n", x1, q, r);

    int x2 = potencia_modular(a, x1, n1);
    int x2q = potencia_modular(x2, q, n1);
    int ar = potencia_modular(a, r, n1);

    printf("a^x1 mod n1 = %d\n", x2);
    printf("x2^q mod n1 = %d\n", x2q);
    printf("a^r mod n1 = %d\n", ar);

    int resultado = (x2q * ar) % n1;
    printf("Resultado final: ((x2^q) * (a^r)) mod n1 = %d\n", resultado);
    return resultado;
}

int main() {
    int H, G, n, x, n1;
    printf("Digite os valores de H, G, n, x e n1: ");
    scanf("%d %d %d %d %d", &H, &G, &n, &x, &n1);

    int a = calcular_base(H, G, n);
    if (a == -1) return 1;

    printf("a = %d\n", a);

    if (calcular_mdc(a, n1) == 1)
        printf("%d e %d sao primos entre si.\n", a, n1);
    else
        printf("%d e %d NAO sao primos entre si.\n", a, n1);

    if (verifica_primo(n1))
        printf("n1 = %d e primo.\n", n1);
    else
        printf("n1 = %d NAO e primo.\n", n1);

    resolver_congruencia(a, x, n1);

    return 0;
}