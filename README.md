# TAC Jogos Eletrônicos

UnB :: Tópicos Avançados em Computadores :: 2021/1

Gabriel Rocha Fontenele :: 15/1026760

## Como executar

Para executar em Windows, baixe o binário de 32-bits compátivel com ambas as edições x86 e x64 disponíveis em [Releases](https://github.com/ngsylar/TAC_JE/releases) e em seguida abra _JOGO.bat_.

Para executar em Linux, leia a seção [Como compilar](#como-compilar).

## Como compilar

Para compilar a partir da pasta raiz, tenha certeza de ter instalado o SDL2 e as bibliotecas adicionais (SDL2_IMG, SDL2_Mix, SDL2_ttf) e no terminal execute:
```bash
make        # para compilar
./JOGO      # para executar
```

* No windows, inclua as dlls necessárias na pasta raiz (para abrir _JOGO.exe_) ou em _extlib_ (para abrir _JOGO.bat_) (veja _[extlib/requirements.txt](extlib/requirements.txt))_.