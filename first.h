#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <stdlib.h>
namespace functions{
    class IGeoFig {
    public :
        virtual double square () = 0 ;
        virtual double perimeter () = 0 ;
    } ;
    class CVector2D {
    public :
        double x, y;
    } ;
    class IPhysObject {
    public :
        virtual double mass () const = 0 ;
        virtual CVector2D position () = 0 ;
        virtual bool operator == ( const IPhysObject& ob ) const = 0 ;
        virtual bool operator < ( const IPhysObject& ob ) const = 0 ;
    } ;
    class IPrintable {
    public :
        virtual void draw () = 0 ;
    } ;
    class IDialogInitiable {
        virtual void initFromDialog () = 0 ;
    } ;
    class BaseCObject {
    public :
        virtual const char * classname () = 0 ;
        virtual unsigned int size () = 0 ;
    } ;

    class MyFigure:
            public IGeoFig,
            public CVector2D,
            public IPhysObject,
            public IPrintable,
            public IDialogInitiable,
            public BaseCObject {
    };

    struct Rectangle: MyFigure {
    private:
        std::pair<double, double> first_coord; //левые верхние
        std::pair<double, double> second_coord; //правые нижние
        std::pair<double, double> third_coord; //левые нижние
        std::pair<double, double> fourth_coord; //правые верхние
        double weight = 0;
    public:
        Rectangle();
        void initFromDialog() override;
        double square() override;
        double perimeter() override;
        [[nodiscard]] double mass() const override;
        CVector2D position() override;
        bool operator == (const IPhysObject& obj) const override;
        bool operator < (const IPhysObject& obj) const override;
        void draw() override;
        const char* classname() override;
        unsigned int size() override;
    };


    struct Segment: MyFigure {
    private:
        std::pair<double, double> first_c;
        std::pair<double, double> second_c;
        double weight = 0;
    public:
        Segment();
        void initFromDialog() override;
        double square() override;
        double perimeter() override;
        [[nodiscard]] double mass() const override;
        CVector2D position() override;
        bool operator == (const IPhysObject& obj) const override;
        bool operator < (const IPhysObject& obj) const override;
        void draw() override;
        const char* classname() override;
        unsigned int size() override;
    };

    class DialogueMenu {
    private:
        std::vector <MyFigure*> figures;
        int flag;
        double summary_perim = 0;
        double summary_sq = 0;
        double summary_weight = 0;
        unsigned int summary_size = 0;

    public:
        DialogueMenu();
        void menufunction();
        void allcommands();
        template<class T>
        void newfigure() {
            auto* figure = new T();
            figure->initFromDialog();
            summary_sq += (figure->square());
            summary_perim += (figure->perimeter());
            summary_weight += (figure->mass());
            summary_size += (figure->size());
            figures.push_back((MyFigure*)figure);
        }
    };
}
