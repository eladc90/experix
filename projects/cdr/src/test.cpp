#include <vector>
#include <iostream>
#include "cdr_dispatcher.hpp"
#include "cdr_threads.hpp"

#include "aggregator.hpp"
#include "mobile_operator.hpp"
#include "operator_aggregator.hpp"
#include "cyc_waitable_queue.hpp"
#include "customer_aggregator.hpp"
#include "customer.hpp"
#include "thread.hpp"
#include "cdr.hpp"


int main()
{
  
  //Create Cdr's

  std::string stingFromFile("30|972040547840875|35-18181818-68686-1|MTC|972547840875|20/02/2020|15:30:25|106|0|0|9720547840865");
  std::string stingFromFile2("30|972020547840875|35-18181818-68686-1|MTC|972547840875|20/02/2020|15:30:25|94|0|0|9720547840865");
  std::string stingFromFile3("30|972040547840875|35-18181818-68686-1|SMS_MO|972547840875|20/02/2020|15:30:25|0|0|0|9720547840865");
  std::string stingFromFile4("30|972020547840875|35-18181818-68686-1|MOC|972547840875|20/02/2020|15:30:25|150|0|0|9720547840865");
  std::string stingFromFile5("30|972040547840875|35-18181818-68686-1|SMS_MT|972547840875|20/02/2020|15:30:25|0|0|0|9720547840865");



  experis::Cdr* cdr1 = new experis::Cdr(stingFromFile);
  experis::Cdr *cdr2 = new experis::Cdr(stingFromFile2);
  experis::Cdr* cdr3 = new experis::Cdr(stingFromFile3);
  experis::Cdr *cdr4 = new experis::Cdr(stingFromFile4);
  experis::Cdr* cdr5 = new experis::Cdr(stingFromFile5);


  //Create Queue
  experis::WaitableQueue<experis::Cdr *>* waitQ = new experis::WaitableQueue<experis::Cdr *>(6);

  waitQ->Enqueue(cdr1);
  waitQ->Enqueue(cdr2);
  waitQ->Enqueue(cdr3);
  waitQ->Enqueue(cdr4);
  waitQ->Enqueue(cdr5);


  experis::CdrDispatcher *cdrDisp = new experis::CdrDispatcher();
  //create Operator Aggregators 
  experis::IAggregator* aggi1 = new experis::OperatorAggregator(cdrDisp);
  experis::IAggregator* aggi2 = new experis::CustomerAggregator(cdrDisp);

  experis::ThreadPool *mainRunner = new experis::ThreadPool(5, cdrDisp, waitQ);  

  //thread that Run all
  experis::Thread *mainThread = new experis::Thread(mainRunner);
 
  
  delete mainThread; 
  delete mainRunner;
  delete waitQ;
  delete aggi1;
  delete aggi2;
  delete cdrDisp;
  return 0;
}
