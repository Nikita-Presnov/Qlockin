#ifndef LOCKIN_H
#define LOCKIN_H
#define PORT_NAME_LEN 13
int screach_lockin(char *idn, char *locname);
class lockin
{
public:
  lockin(char *comname);
  int get_data(char *command);
  int send_command(char *command);
  int F_ID;
  char data[20];
};

#endif // LOCKIN_H
