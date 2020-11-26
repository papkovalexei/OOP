#ifndef H_CARD
#define H_CARD

#include <string>
#include <iostream>

class ccard
{
public:
    ccard() {}

    ccard(int id_bank, int id_program, int id_card)
        : _id_bank(id_bank), _id_program(id_program), _id_card(id_card)
    {}

    int get_id_bank() const
    {
        return _id_bank;
    }

    int get_id_program() const
    {
        return _id_program;
    }

    int get_id_card() const
    {
        return _id_card;
    }

    std::string get_number() const
    {
        std::string result = convert_to_output(_id_bank);
        result += " ";
        result += convert_to_output(_id_program);
        result += " ";
        result += convert_to_output(_id_card);

        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, ccard& card)
    {
        os << card.convert_to_output(card._id_bank) << " " << card.convert_to_output(card._id_program)
            << " " << card.convert_to_output(card._id_card) << std::endl;

        return os;
    }

private:
    int _id_bank;
    int _id_program;
    int _id_card;

    std::string convert_to_output(int number) const
    {
        std::string answer = "";

        if (number < 1000 && number >= 100)
            answer += "0";
        else if (number < 100 && number >= 10)
            answer += "00";
        else if (number < 10)
            answer += "000";
        answer += std::to_string(number);

        return answer;
    }
};

#endif