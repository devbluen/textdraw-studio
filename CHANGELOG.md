# Changelog

Todas as alterações relevantes em cima do **Textdraw Studio v1.6.0** (open.mp). Versão atual: **v1.7.0**.

## [1.7.0] - 2026-09-02

### Adicionado

- Sistema de multi-linguagem no gamemode, com quatro idiomas:
  - Inglês (`en`)
  - Português (BR) (`pt`) — idioma padrão
  - Espanhol (`es`)
  - Francês (`fr`)
- Seletor de idioma nas **Definições** da taskbar e pelos comandos `/lang` e `/language`.
- Persistência da preferência por nome do jogador na tabela SQLite `user_language`.
- API de tradução para o código:
  - `L(playerid, E_LANG_...)` — texto estático
  - `LangF(...)` — texto com `format`
  - `SendLang(...)` — mensagem no chat
- Packs de strings em `gamemodes/src/utils/lang/`.
- Configuração do compilador Pawn (qawno / open.mp) no Cursor/VS Code:
  - associação `*.pwn` / `*.inc`
  - caminho do `qawno/pawncc.exe`
  - extensão recomendada `southclaws.vscode-pawn`
- `compile.bat` na raiz para compilar o `main.pwn` sem abrir o editor.

### Alterado

- Versão do projeto: `v1.6.0` → `v1.7.0` (`STUDIO_VERSION` e `version.txt`).
- Diálogos, mensagens e dicas da taskbar passaram a usar chaves de idioma em vez de texto fixo em inglês.
- Campo `language` do `config.json` (omp-server) atualizado para `PT-BR / EN / ES / FR`.

### Ficheiros

#### Novos

- `CHANGELOG.md`
- `gamemodes/src/utils/lang/keys.inc`
- `gamemodes/src/utils/lang/lang.inc`
- `gamemodes/src/utils/lang/en.inc`
- `gamemodes/src/utils/lang/pt.inc`
- `gamemodes/src/utils/lang/es.inc`
- `gamemodes/src/utils/lang/fr.inc`

#### Alterados

- `version.txt`
- `config.json`
- `gamemodes/src/utils/variables.inc`
- `gamemodes/main.pwn`
- `gamemodes/src/connections/connection.inc`
- `gamemodes/src/connections/tables.inc`
- `gamemodes/src/general/misc/camera/camera.inc`
- `gamemodes/src/general/misc/imports/imports.inc`
- `gamemodes/src/general/session/components/events/groups/draws.inc`
- `gamemodes/src/general/session/components/events/groups/items.inc`
- `gamemodes/src/general/session/components/events/groups/list.inc`
- `gamemodes/src/general/session/components/functions/textdraw/textdrawColorPick.inc`
- `gamemodes/src/general/spriteBrowser/spriteBrowser.inc`
- `gamemodes/src/general/taskbar/components/events/buttons/copy.inc`
- `gamemodes/src/general/taskbar/components/events/buttons/create.inc`
- `gamemodes/src/general/taskbar/components/events/buttons/delete.inc`
- `gamemodes/src/general/taskbar/components/events/buttons/list.inc`
- `gamemodes/src/general/taskbar/components/events/buttons/model.inc`
- `gamemodes/src/general/taskbar/components/events/buttons/outline.inc`
- `gamemodes/src/general/taskbar/components/events/buttons/projects/packages/create.inc`
- `gamemodes/src/general/taskbar/components/events/buttons/projects/packages/export.inc`
- `gamemodes/src/general/taskbar/components/events/buttons/projects/packages/import.inc`
- `gamemodes/src/general/taskbar/components/events/buttons/projects/packages/list.inc`
- `gamemodes/src/general/taskbar/components/events/buttons/projects/packages/management.inc`
- `gamemodes/src/general/taskbar/components/events/buttons/settings.inc`
- `gamemodes/src/general/taskbar/components/events/buttons/shadow.inc`
- `gamemodes/src/general/taskbar/components/events/buttons/text.inc`
- `gamemodes/src/general/taskbar/components/events/moviment.inc`
- `gamemodes/src/general/taskbar/views/default.inc`
- `gamemodes/src/utils/times.inc`
- `gamemodes/src/utils/web_colors.inc`

### Notas

- Para acrescentar uma string: criar a chave no enum de `keys.inc`, adicionar a linha na **mesma ordem** em `en.inc`, `pt.inc`, `es.inc` e `fr.inc`, e usar `L(playerid, E_LANG_...)` no código.