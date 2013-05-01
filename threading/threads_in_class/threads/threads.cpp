// threads.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

DWORD __stdcall StartEmployee(LPVOID arg);

class Employee
{
public:
  std::string name;
  bool working;
  virtual void startShift()
  {
	working = true; 
	HANDLE h = CreateThread(NULL,1000,StartEmployee,this,0,0);
	if (h == NULL) {
		std::cout << name << " could not start working." << std::endl;
		working = false;
	}
  }
  virtual void goHome()
  {
	working = false;
  }

  virtual void work()
  {
	  while (working) doJob();
  }
  virtual void doJob() {};
};

DWORD __stdcall StartEmployee(LPVOID arg)
{
  ((Employee*)arg)->work();
  return 0;
}

class Food
{
public:
  std::string name;
  void random()
  {
	  switch(rand()%4) {
	  case 0: name="burrito"; break;
	  case 1: name="taco"; break;
	  case 2: name="gordita"; break;
	  case 3: name="salad"; break;
	  }
  }
};

class Order
{
public:
  std::list < Food > items;
  int customer;
  static int count;
  void random()
  {
	  customer = count%1000+1;
	  ++count;
	  int n = rand()%4 + 1;
	  for (int i=0; i<n; ++i) {
		  Food food;
		  food.random();
		  items.push_back(food);
	  }
  }
};

int Order::count = 0;

class Orders
{
private:
	std::list < Order > data;
	HANDLE mutex;
	void enter()
	{
		WaitForSingleObject(mutex,INFINITE);
	}
	void exit()
	{
		ReleaseMutex(mutex);
	}
public:
	Orders()
	{
		mutex = CreateMutex(0,FALSE,NULL);
	}
	bool pop(Order &order)
	{
		bool ans;
		enter();
		if (data.empty()) {
			ans = false;
		} else {
			ans = true;
		    order = data.front();
		    data.pop_front();
		}
		exit();
		return ans;
	}
	void push(Order order)
	{
		enter();
		data.push_back(order);
		exit();
	}
	bool empty()
	{
		bool ans;
		enter();
		ans = data.empty();
		exit();
		return ans;
	}
};

Orders unprepared;
Orders prepared;

class Cook : public Employee
{
public:
  Order cooking;
  void doJob()
  {
	  if (unprepared.pop(cooking)) {
		  Sleep(rand()%1000);
		  prepared.push(cooking);
	  } else {
		  Sleep(rand()%100);
	  }
  }
  // prepares the burrito, puts cooked burritos in the window
};

class Expeditor : public Employee
{
public:
  void callOutPreparedOrders()
  {
	  Order current;
	  while (prepared.pop(current)) {
		  std::cout << "Customer # " << 
			  current.customer << 
			  ", your order is ready!" << std::endl;

		  Sleep(rand()%1000);

	  }
  }
  void doJob()
  {
	  callOutPreparedOrders();
  }
};

class Cashier : public Employee
{
public:
  void createUnpreparedOrder()
  {
	  Order order;
	  order.random();
	  unprepared.push(order);
  }
  void doJob()
  {
	  Sleep(rand()%1000);
	  createUnpreparedOrder();
  }
};


int _tmain(int argc, _TCHAR* argv[])
{
	Cashier *bill = new Cashier();
	bill->name = "bill";
	int ncooks = 100;
	std::list < Cook* > cooks;

	for (int i=0; i<ncooks; ++i) {
		cooks.push_back(new Cook());
	}
	Expeditor *susan = new Expeditor();
	susan->name = "susan";
	bill->startShift();
	int cookie = 1;
	for (std::list < Cook* > :: iterator i = cooks.begin(); 
		i != cooks.end();
		++i) {
			std::ostringstream oss;
			oss << "cook # " << cookie;
			(*i)->name=oss.str();
			(*i)->startShift();
			++cookie;
	}
	susan->startShift();

	Sleep(10000);
	bill->goHome();
	for (std::list < Cook* > :: iterator i = cooks.begin(); 
		i != cooks.end();
		++i) {
			(*i)->goHome();
	}
	susan->goHome();
	return 0;
}

