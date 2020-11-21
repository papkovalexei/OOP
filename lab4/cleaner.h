#ifndef H_CLEANER
#define H_CLEANER

#include <ctime>
#include <algorithm>
#include <iostream>

#include "_restore_point.h"
#include "restore_point_inc.h"

#define MODE_TIME 1
#define MODE_COUNT 2
#define MODE_SIZE 4

#define MODE_DELETE_ALL 1
#define MODE_DELETE_ONE 2

class cleaner
{
public:
    cleaner() 
        : _size(-1), _count(-1), _time(-1) 
    {}

    cleaner(int size, int count, time_t time)
        : _size(size), _count(count), _time(time)
    {}

    std::vector<std::map<int, _restore_point*>::iterator> clean_count(std::map<int, _restore_point*>& points)
    {
        std::vector<std::map<int, _restore_point*>::iterator> answer;
        int buffer_count = 0;

        if (points.size() <= _count)
            return answer;

        auto it = points.end();
        auto it_last = points.end();

        do
        {
            it--;
            buffer_count++;
            
            if (buffer_count == _count)
            {
                while (dynamic_cast<restore_point_inc*>((*it).second))
                        it--;
                if (it == points.begin())
                    return answer;
                it_last = --it;

                break;
            }

        } while (it != points.begin());
        
        for (it = points.begin(); it != it_last; it++)
            answer.push_back(it);
        answer.push_back(it_last);
        
        return answer;
    }

    std::vector<std::map<int, _restore_point*>::iterator> clean_size(std::map<int, _restore_point*>& points, int size)
    {
        std::vector<std::map<int, _restore_point*>::iterator> answer;
        int buffer_size = 0;

        if (size <= _size)
            return answer;

        auto it = points.end();
        auto it_last = points.end();

        do
        {
            it--;

            if (buffer_size + (*it).second->get_size() >= _size)
            {
                while (dynamic_cast<restore_point_inc*>((*it).second))
                    it--;

                if (it == points.begin())
                    return answer;
                it_last = --it;
                break;
            }
            else
                buffer_size += (*it).second->get_size();
        } while (it != points.begin());
        
        for (it = points.begin(); it != it_last; it++)
            answer.push_back(it);
        answer.push_back(it_last);
        
        return answer;
    }

    std::vector<std::map<int, _restore_point*>::iterator> clean_time(std::map<int, _restore_point*>& points)
    {
        std::vector<std::map<int, _restore_point*>::iterator> answer;

        auto it = points.end();
        auto it_last = points.end();

        while (it != points.begin())
        {
            if (it == points.end())
            {
                it--;
                continue;
            }

            if ((*it).second->get_creation_time() < _time)
            {
                it++;

                if (it != points.end())
                {
                    if (dynamic_cast<restore_point_inc*>((*it).second))
                    {
                        while (dynamic_cast<restore_point_inc*>((*it).second))
                            it--;

                        if (it == points.begin())
                            return answer;
                        it_last = --it;
                    }
                    else
                    {
                        it_last = --it;
                    }
                }
                else
                    it_last = --it;
                break;
            }

            it--;
        }

        if (it_last == points.end())
            return answer;

        for (it = points.begin(); it != it_last; it++)
            answer.push_back(it);
        answer.push_back(it_last);
        
        return answer;
    }

    std::vector<std::map<int, _restore_point*>::iterator> clean_gybrid(std::map<int, _restore_point*>& points, int mode, int when)
    {
        int answer_offset;
        std::vector<std::map<int, _restore_point*>::iterator> answer;
        std::vector<int> points_offset;

        if (mode & MODE_COUNT)
        {
            points_offset.push_back(clean_count(points).size());
        }

        if (mode & MODE_SIZE)
        {
            int size = 0;
            for (auto it = points.begin(); it != points.end(); it++)
                size += (*it).second->get_size();

            points_offset.push_back(clean_size(points, size).size());
        }

        if (mode & MODE_TIME)
            points_offset.push_back(clean_time(points).size());

        if (when == MODE_DELETE_ALL)
            answer_offset = (*std::min_element(points_offset.begin(), points_offset.end()));
        else
            answer_offset = (*std::max_element(points_offset.begin(), points_offset.end()));

        std::cout << "remove: " << answer_offset << std::endl;
        
        int i = 0;

        for (auto it = points.begin(); it != points.end(); it++, i++)
        {
            if (i == answer_offset)
                break;
            answer.push_back(it);
        }

        return answer;
    }
protected:
    int _size;
    int _count;
    time_t _time;
};

#endif