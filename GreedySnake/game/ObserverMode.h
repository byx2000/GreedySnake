#pragma once

#include <vector>
#include <algorithm>

using namespace std;

class Listener
{
public:
    virtual void update(int msg) = 0;
};

class DataSource
{
protected:
    vector<Listener*> listeners;
public:
    void registerListener(Listener* listener);
    void removeListener(Listener* listener);
    void notifyListeners(int msg);
};
