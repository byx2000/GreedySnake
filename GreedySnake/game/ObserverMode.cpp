#include "ObserverMode.h"

void DataSource::registerListener(Listener* listener)
{
    listeners.push_back(listener);
}

void DataSource::removeListener(Listener* listener)
{
    vector<Listener*>::iterator it = find(listeners.begin(), listeners.end(), listener);
    if (it != listeners.end())
    {
        listeners.erase(it);
    }
}

void DataSource::notifyListeners(int msg)
{
    for (size_t i = 0; i < listeners.size(); ++i)
    {
        listeners[i]->update(msg);
    }
}
