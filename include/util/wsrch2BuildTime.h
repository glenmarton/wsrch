#ifndef D_wsrch2BuildTime_H
#define D_wsrch2BuildTime_H

///////////////////////////////////////////////////////////////////////////////
//
//  wsrch2BuildTime is responsible for recording and reporting when
//  this project library was built
//
///////////////////////////////////////////////////////////////////////////////

class wsrch2BuildTime
  {
  public:
    explicit wsrch2BuildTime();
    virtual ~wsrch2BuildTime();
    
    const char* GetDateTime();

  private:
      
    const char* dateTime;

    wsrch2BuildTime(const wsrch2BuildTime&);
    wsrch2BuildTime& operator=(const wsrch2BuildTime&);

  };

#endif  // D_wsrch2BuildTime_H
