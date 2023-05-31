/*

*/

#ifndef DATA_H
#define DATA_H

class Data
{
public:
  Data(void);

  void setData(String data);

  String getData(void);

  void setTimezoneType(String type);

  String getTimezoneType(void);

  void setTimezone(int timezone);

  int getTimezone(void);

private:
  String _data;
  String _timezone_type;
  int _timezone;
};

#endif