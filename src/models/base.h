#ifndef BASE_H
#define BASE_H

class Base {
    private:
        double price;
    public:
        Base();
        virtual double get_price() const;
};

#endif