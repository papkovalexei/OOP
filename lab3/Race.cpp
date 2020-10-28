#include "Race.h"

Race::Race()
{
    _distance = DISTANCE;
}

Race::Race(float distance)
    : _distance(distance)
{
    if (distance <= 0)
    {
        this->~Race();
        throw Error::INCORRECT_DISTANCE;
    }
}

Race::~Race()
{

}

float Race::getDistance() const
{
    return _distance;
}

void Race::setDistance(float distance)
{
    _distance = distance;
}

bool compare(std::pair<float, int> l, std::pair<float, int> r)
{
    return l.first < r.first;
}

void Race::addTransport(Transport* transport)
{
    _transport.push_back(transport);
}

std::vector<Transport*> Race::run()
{
    std::vector<std::pair<float, int>> times(_transport.size());
    std::vector<Transport*> answer;

    for (int i = 0; i < _transport.size(); i++)
        times[i] = std::pair<float, int>((*_transport[i]).move(_distance), i);
    std::sort(times.begin(), times.end(), compare);

    if (times.size() > 1)
    {
        if (times[0].first != times[1].first)
        {
            answer.push_back(_transport[times[0].second]);
        }
        else
        {
            for (int i = 0; i < times.size(); i++)
            {
                if (i == 0)
                    answer.push_back(_transport[times[i].second]);
                else if (times[i].first == times[0].first)
                    answer.push_back(_transport[times[i].second]);
                else
                    break;
            }
        }
    }
    else
        answer.push_back(_transport[times[0].second]);
    return answer;
}