# Définition de la variable de bascule
IS_LIBFT ?= false

# 🛠 Compilateur et flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra
LDFLAGS =

# 🏆 Nom du projet
PROJECT_NAME = philo

# 🖥️ Détection de l'OS
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	CFLAGS   += -I/usr/include
	LDFLAGS  += -L/usr/lib
else ifeq ($(UNAME_S), Darwin)
	CFLAGS   += -I/opt/homebrew/include
	LDFLAGS  += -L/opt/homebrew/lib -framework Cocoa
else ifeq ($(UNAME_S), Windows_NT)
	CFLAGS   +=
	LDFLAGS  +=
endif

# 📂 Répertoires
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

# 📌 Fichiers sources et objets
SRC_FILES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# 📚 Inclusion des headers
INCLUDES = -I$(INCLUDE_DIR)

ifeq ($(IS_LIBFT), true)
	# 🔧 Configuration de libft
	LIBFT_DIR = mylib
	LIBFT = $(LIBFT_DIR)/lib/libft.a
	LIBFT_REPO = https://github.com/Corgidev42/mylib.git
	LIBFT_INCLUDE = -I$(LIBFT_DIR)/include
	INCLUDES += $(LIBFT_INCLUDE)
endif

# 🎯 Règle principale
all: $(PROJECT_NAME)

ifeq ($(IS_LIBFT), true)
# 🏗️ Création de l'exécutable avec libft
$(PROJECT_NAME): $(LIBFT) $(OBJ_FILES)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ_FILES) $(LDFLAGS) $(LIBFT) -o $@
	@echo "✅ Compilation terminée avec libft !"
else
# 🏗️ Création de l'exécutable sans libft
$(PROJECT_NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ_FILES) $(LDFLAGS) -o $@
	@echo "✅ Compilation terminée sans libft !"
endif

# 🛠️ Compilation des fichiers objets (prise en charge des sous-dossiers)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
	@echo "🔨 Compilé : $< -> $@"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

ifeq ($(IS_LIBFT), true)
# 📦 Clonage de libft (si nécessaire)
$(LIBFT_DIR):
	git clone $(LIBFT_REPO) $(LIBFT_DIR)

# 📦 Compilation de libft (seulement si nécessaire)
$(LIBFT): | $(LIBFT_DIR)
	@if [ ! -f $(LIBFT) ]; then \
		echo "📥 Compilation de libft..."; \
		make -C $(LIBFT_DIR); \
	else \
		echo "✅ libft déjà compilée."; \
	fi
endif

# 🧹 Nettoyage des fichiers objets
clean:
	rm -rf $(OBJ_DIR)
ifeq ($(IS_LIBFT), true)
	if [ -d $(LIBFT_DIR) ]; then make -C $(LIBFT_DIR) clean; fi
endif
	@echo "🗑️  Fichiers objets nettoyés."

# 🗑️ Nettoyage complet (objets, exécutable ET, si applicable, libft)
fclean: clean
	rm -f $(PROJECT_NAME)
ifeq ($(IS_LIBFT), true)
	rm -rf $(LIBFT_DIR)
endif
	@echo "🗑️  Nettoyage complet effectué."

# 🔄 Reconstruction
re: fclean all

# ▶️ Exécution du projet avec support d'arguments (optionnel)
run: all
	./$(PROJECT_NAME) $(ARGS)

.PHONY: all clean fclean re run
