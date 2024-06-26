# Projeto Sockets #
### Instalação ###
Para compilar o código execute o seguinte código:
``` make all```
O comando vai gerar dois arquivos binários, *client* e *server*, que devem ser executados separadamente, seja na mesma máquina (localhost), ou em computadores diferentes.

### Utilização ###
Primeiro, o servidor deve abrir uma conexão de acordo com a porta informada pelo usuário, e em seguida, aguarda a requisição para se conectar com o cliente.

No cliente, o usuário informa o endereço de IP do servidor (se for localhost, ip="127.0.0.1") e a porta que o servidor abriu. Uma vez conectados, os usuários podem trocar mensagens entre sí.

Para verificar o funcionamento do algoritmo utilizado para a codificaçao de linha 2B1Q, o usuário pode clicar no botão da seção inferior "Prova Real", que sobrescreve as etapas de criptografia e conversão para binário, plotando, efetivamente, apenas os sinais gerados pela sequência de bits "0011011001" após a conversão para 2B1Q.

### Codificação ###
Para codificar as mensagens enviadas, foi utilizado o algoritmo de codificação de linha 2B1Q. Além disso, para encriptografar os textos enviados, foi utilizado o algoritmo de criptografia RCA com números primos baixos. 

Na seção de mensagens, em ambos os hosts, é mostrado a mensagem recebida criptografada, sua forma em binário e sua forma descriptografada. Além disso, os sinais gerados pela codificação de linha são mostrados em um gráfico na seção inferior.