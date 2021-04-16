#ifndef LOCKIN_H
#define LOCKIN_H
#define PORT_NAME_LEN 13
#define IDN1 "81595"
#define IDN2 "70259"
bool screach_lockin(char *idn, char *locname);
class lockin
{
public:
    lockin();
    bool init(char *comname);
    bool get_data();//char *command);
    int send_command(char *command);
    void close_lockin();
    int F_ID;
    char data[20];
};

#endif // LOCKIN_H
