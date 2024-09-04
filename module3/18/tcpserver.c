
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>

#define MAX_CLIENTS 1024


// количество активных пользователей
int nclients = 0;

// печать количества активных
// пользователей
void printusers() {
	if(nclients) 
		printf("%d user on-line\n",nclients);
	else 
		printf("No User on line\n");
}

// сумма
int sum(int a, int b) {
	return a + b;
}

// функция обработки ошибок
void error(const char *msg) {
	perror(msg);
	exit(1);
}

// функция обслуживания
// подключившихся пользователей
void dostuff (int sock) {
  int bytes_recv; // размер принятого сообщения
  int a,b; // переменные для математических действий
  char action;
  char buff[20 * 1024];

  #define str1 "Enter 1 parameter\r\n"
  #define str2 "Enter 2 parameter\r\n"
  #define str3 "Enter action (+, -, /, *)\r\n"

  write(sock, str3, strlen(str3)); // Используйте strlen вместо sizeof

  bytes_recv = read(sock, &buff[0], sizeof(buff) - 1); // Оставляем место для нуль-терминатора
  if (bytes_recv < 0) 
    error("ERROR reading from socket");
  buff[bytes_recv] = '\0'; // Добавить нуль-терминатор
  action = buff[0];
  
  write(sock, str1, strlen(str1));
  
  // обработка первого параметра
  bytes_recv = read(sock, &buff[0], sizeof(buff) - 1);
  if (bytes_recv < 0) 
    error("ERROR reading from socket");
  buff[bytes_recv] = '\0'; // Добавить нуль-терминатор
  a = atoi(buff); // преобразование первого параметра в int

  write(sock, str2, strlen(str2));

  // обработка второго параметра
  bytes_recv = read(sock, &buff[0], sizeof(buff) - 1);
  if (bytes_recv < 0) 
    error("ERROR reading from socket");
  buff[bytes_recv] = '\0'; // Добавить нуль-терминатор
  b = atoi(buff); // преобразование второго параметра в int

  // Выполняем действие в зависимости от action
  switch (action) {
      case '+':
          a = sum(a, b);
          break;
      case '-':
          a = a - b;
          break;
      case '*':
          a = a * b;
          break;
      case '/':
          if (b != 0) a = a / b;
          else {
              snprintf(buff, sizeof(buff), "ERROR: Division by zero\n");
              write(sock, buff, strlen(buff));
              nclients--;
              printf("-disconnect\n");
              printusers();
              return;
          }
          break;
      default:
          snprintf(buff, sizeof(buff), "ERROR: Invalid action\n");
          write(sock, buff, strlen(buff));
          nclients--;
          printf("-disconnect\n");
          printusers();
          return;
  }

  // Подготовка результата и отправка клиенту
  snprintf(buff, sizeof(buff), "%d\n", a); // Формируем результат
  write(sock, buff, strlen(buff)); // Отправляем результат
  nclients--; // уменьшаем счетчик активных клиентов
  printf("-disconnect\n");
  printusers();
  
  return;
}


int main(int argc, char *argv[])
{
	char buff[1024]; // Буфер для различных нужд

	int sockfd, newsockfd, // дескрипторы сокетов
	 	portno, // номер порта
	 	pid; // id номер потока

	int client_sockets[MAX_CLIENTS];

	fd_set readfds;

	socklen_t clilen; // размер адреса клиента типа socklen_t
	struct sockaddr_in serv_addr, cli_addr; // структура сокета сервера и клиента
	printf("==TCP SERVER==\n");

	// ошибка в случае если мы не указали порт
	if (argc < 2) {
		fprintf(stderr, "ERROR, no port provided\n");
		exit(1);
	}

	// Шаг 1 - создание сокета
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");

	// Шаг 2 - связывание сокета с локальным адресом
	bzero((char*) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY; // сервер принимает подключения на все IP-адреса
	serv_addr.sin_port = htons(portno);

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR on binding");

	// Шаг 3 - ожидание подключений, размер очереди - 5
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);

	// Шаг 4 - извлекаем сообщение из очереди (цикл извлечения запросов на подключение)
	
	for (int i = 0; i < MAX_CLIENTS; i++)
				client_sockets[i] = -1;

  FD_ZERO(&readfds);
  FD_SET(sockfd, &readfds);
  int max_fd = sockfd;

 
  

	while (1)
	{

    fd_set temp_fds = readfds;
    // Ждем событий на сокетах
    int ready = select(max_fd + 1, &temp_fds, NULL, NULL, NULL);

    if (ready < 0)
        error("ERROR on select");
    
	for (int i = 0; i <= max_fd; i++) 
	{
       	if (FD_ISSET(i, &temp_fds)) 
       	{
            if (i == sockfd) 
            {
                // Новое входящее соединение
                newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
                if (newsockfd < 0) 
                    error("ERROR on accept");
                    

                    // Добавляем новый сокет в массив
                for (int j = 0; j < MAX_CLIENTS; j++) 
                {
                	if (client_sockets[j] == -1) 
                	{
                    	client_sockets[j] = newsockfd;
                        nclients++;
                        break;
                    }
                }    

                // Добавляем новый сокет в множество readfds
                FD_SET(newsockfd, &readfds);
                if (newsockfd > max_fd) 
                	 max_fd = newsockfd;
                    

                // Вывод сведений о клиенте
                struct hostent *hst;
                hst = gethostbyaddr((char *) &cli_addr.sin_addr, 4, AF_INET);
                printf("+%s [%s] new connect!\n",
                  (hst) ? hst->h_name : "Unknown host",
                   (char *) inet_ntoa(cli_addr.sin_addr));
                printusers();
                dostuff(newsockfd);
            } 
               
        
      	}
    }
	}
	close(sockfd);
	return 0;
}