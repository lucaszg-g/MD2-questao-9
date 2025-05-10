/*
Questão 9 – Primeira prova  
Matéria: Matemática Discreta 2  
Professora: Cristiane Loesch  
Aluno: Lucas Gabriel Gomes Aguiar  
Matrícula: 232004506  
*/

#include <stdio.h>
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
    printf("\n--- Etapa 1: Calculo da base 'a' tal que a seja equivalente a H * G^(-1) mod n ---\n");

    if (calcular_mdc(G, n) != 1) {
        printf("Como mdc(%d, %d) != 1, G e n nao sao primos entre si. O inverso modular nao existe.\n", G, n);
        return -1;
    }

    int inverso = inverso_modular(G, n);
    if (inverso == -1) {
        printf("Erro ao calcular o inverso modular.\n");
        return -1;
    }

    printf("O inverso modular de %d mod %d e: %d\n", G, n, inverso);

    int resultado = (H * inverso) % n;
    if (resultado < 0) resultado += n;
    printf("Logo, a = (H * G^(-1)) mod n = (%d * %d) mod %d = %d\n", H, inverso, n, resultado);

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
    printf("\n--- Etapa 2: Resolvendo a congruencia a^x mod n1 ---\n");

    int x1;
    if (verifica_primo(n1)) {
        x1 = n1 - 1;
        printf("Como %d e primo, aplicamos o Pequeno Teorema de Fermat: x1 = %d - 1 = %d\n", n1, n1, x1);
    } else {
        x1 = phi(n1);
        printf("Como %d NAO e primo, usamos a funcao totiente de Euler: phi(%d) = %d\n", n1, n1, x1);
    }

    int q = x / x1;
    int r = x % x1;
    printf("Decompondo x = x1 * q + r: %d = %d * %d + %d\n", x, x1, q, r);

    int x2 = potencia_modular(a, x1, n1);
    int x2q = potencia_modular(x2, q, n1);
    int ar = potencia_modular(a, r, n1);

    printf("a^x1 mod n1 = %d^%d mod %d = %d\n", a, x1, n1, x2);
    printf("(a^x1)^q mod n1 = %d^%d mod %d = %d\n", x2, q, n1, x2q);
    printf("a^r mod n1 = %d^%d mod %d = %d\n", a, r, n1, ar);

    int resultado = (x2q * ar) % n1;
    printf("Resultado final: (x2^q * a^r) mod n1 = (%d * %d) mod %d = %d\n", x2q, ar, n1, resultado);
    return resultado;
}

int main() {
    int H, G, n, x, n1;
    printf("Digite os valores de H, G, n, x e n1: ");
    scanf("%d %d %d %d %d", &H, &G, &n, &x, &n1);

    int a = calcular_base(H, G, n);
    if (a == -1) return 1;

    printf("\n--- Verificacoes adicionais ---\n");
    printf("a = %d\n", a);

    if (calcular_mdc(a, n1) == 1)
        printf("%d e %d sao primos entre si (mdc = 1).\n", a, n1);
    else
        printf("%d e %d NAO sao primos entre si (mdc ≠ 1).\n", a, n1);

    if (verifica_primo(n1))
        printf("%d e um numero primo.\n", n1);
    else
        printf("%d NAO e um numero primo.\n", n1);

    resolver_congruencia(a, x, n1);

    return 0;
}
