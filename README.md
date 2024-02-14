# IRC_42

Starting the server :

`./ircserv <port> <password>`

| Client actions | Execution |
|----------|----------|
|Change username : | /user <new username> |
|Change nickname : | /nick <new nickname> |

| Messaging actions | Execution |
|----------|----------|
| To send a private message : 			   | /msg <username> <message>	|
| To switch between/to a private message channel : | /query <username>  	|
| To leave the private message channel :	   | /query 			|

| Channel actions | Execution |
|----------|----------|
|To join/create a channel : | /join <channel name> |
|To leave the channel : | /leave |
|Kick (operator privilage) : | /kick <username> |
|Invite a user to the channel : | /invite <username> |
|Change channel topic : | /topic <topic name> |
|Set/remove the invite-only channel : | /mode +i/-i |
|Set/remove the restriction of the TOPIC to operator : | /mode +t/-t |
|Set/remove the channel key (password) : | /mode +k/-k <password> |
|Set/remove the user limit to channel : | /mode +l/-l <limit> |

Channel rules:
1.	If the channel does not exist, the one joining it first, 
	Creates the channel and becomes the channel operator
2.	If the channel has no password set, anyone can join
3.	If the password is set, a client connecting to the channel has to specify it
4.	If the channel is set to invite-only, password is not necessary but
	the client has to be invited by someone inside the channel
5. 	If the client limit set is to a lower limit then the current 
	amount of joined Clients, nobody will be kicked but if someone leaves,
	they cant connect back, same applies to new join tries
5.	Operator only commands : MODE & KICK
	

IRC can be tested with nc(netcat) as well.

Linux instalation : 
`sudo apt-get install netcat`

NC usage
Connecting with NC (Steps 2-4 need no order):
| Step | Execution |
|----------|----------|
| 1.	| nc   `<ip adress> <port>` |
| 2.	| NICK `<nickname>`	    |
| 3.	| USER `<username>`	    |
| 4.	| PASS `<password>` 	    |

| Action | Command |
|----------|----------|
| Join a channel		     | JOIN <#channelname>		      |
| Direct private message	     | PRIVMSG username :message	      |
| Channel message		     | PRIVMSG #channelname :message	      |
| Set/remove channel password	     | MODE	#channelname +k/-k password   |
| Set/remove channel limit	     | MODE	#channelname +l/-l limit      |
| Add/remove channel operator	     | MODE	#channelname +o/-o nickname   |
| Set/remove channel topic privilege | MODE	#channelname +t/-t	      |
| Set/remove channel to invite only  | MODE	#channelname +i/-i	      |
| Kick client from a channel	     | KICK	#channelname nickname :reason |
