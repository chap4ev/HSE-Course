#include <iostream>


class Car{
public:
    int doors = 0;
    int wheels = 0;
    int cylinders = 0;

    void ListParts()const{
        std::cout << "Car parts: ";
        std::cout << "Doors: " << doors << "\n";
        std::cout << "Doors: " << wheels << "\n";
        std::cout << "Doors: " << cylinders << "\n";
    }
};


class CarBuilder{
private:

    Car* car;

public:

    CarBuilder(){
        this->Reset();
    }

    ~CarBuilder(){
        delete car;
    }

    void Reset(){
        this->car= new Car();
    }


    void AddDoors(int d)const{
        this->car->doors += d;
    }

    void AddWheels(int w)const{
        this->car->wheels += w;
    }

    void AddCylinders(int c)const{
        this->car->cylinders += c;
    }

    Car* GetProduct() {
        Car* result= this->car;
        this->Reset();
        return result;
    }
};


class Director{
private:
    CarBuilder* builder;

public:

    void set_builder(CarBuilder* builder){
        this->builder=builder;
    }

    void BuildBasicCar(){
        this->builder->AddDoors(2);
        this->builder->AddWheels(4);
        this->builder->AddCylinders(6);
    }
    
    void BuildLuxuryCar(){
        this->builder->AddDoors(4);
        this->builder->AddWheels(4);
        this->builder->AddCylinders(12);
    }
};


int main(){
    Director* director= new Director();
    CarBuilder* builder = new CarBuilder();

    director->set_builder(builder);
    director->BuildBasicCar();
    
    Car* p= builder->GetProduct();
    p->ListParts();
    delete p;

    director->BuildLuxuryCar();

    p= builder->GetProduct();
    p->ListParts();
    delete p;

    delete builder;
    delete director;
    return 0;    
}