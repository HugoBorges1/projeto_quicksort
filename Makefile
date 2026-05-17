CC = clang
CFLAGS = -Wall -O3

TARGETS_RAIZ = gera_vetor qs_padrao
TARGETS_VAR = qs_original qs_pivo_aleatorio qs_mediana3
TARGETS_MATH = qs_limite100_pivo_aleatorio qs_limite100_mediana3

all: $(TARGETS_RAIZ) $(TARGETS_VAR) $(TARGETS_MATH)

$(TARGETS_RAIZ): %: %.c
	$(CC) $(CFLAGS) $< -o $@

$(TARGETS_VAR): %: variantes_quicksort/%.c
	$(CC) $(CFLAGS) $< -o $@

$(TARGETS_MATH): %: variantes_quicksort/%.c
	$(CC) $(CFLAGS) $< -o $@ -lm

clean:
	rm -f $(TARGETS_RAIZ) $(TARGETS_VAR) $(TARGETS_MATH)