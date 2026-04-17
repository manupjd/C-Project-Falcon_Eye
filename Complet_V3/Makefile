# Nom de l'exécutable final
TARGET = falcon_eye

# Compilateur
CC = gcc

# Options de compilation (Warnings pour éviter les erreurs bêtes)
CFLAGS = -Wall -Wextra -std=c11

# Liste des fichiers sources (.c)
SRCS = main.c graph.c knapsack.c

# Transformation de la liste des .c en .o (fichiers objets)
OBJS = $(SRCS:.c=.o)

# Règle par défaut : compile tout
all: $(TARGET)

# Liaison des fichiers objets pour créer l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compilation de chaque fichier .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers temporaires
clean:
	rm -f $(OBJS) $(TARGET)

# Nettoyage complet
fclean: clean
	rm -f $(TARGET)

# Évite les conflits avec des fichiers qui porteraient le même nom que les règles
.PHONY: all clean fclean