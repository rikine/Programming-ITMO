#include <string>
#include <iostream>
#pragma once
// Интерфейс "Геометрическая фигура".
class IGeoFig {
public:
	// Площадь.
	virtual double square() const = 0;
	// Периметр.
	virtual double perimeter() const = 0;
};
// Вектор
class Vector2D {
public:
	double x, y;
};
// Интерфейс "Физический объект".
class IPhysObject {
public:
	// Масса, кг.
	virtual double mass() const = 0;
	// Координаты центра масс, м.
	virtual Vector2D position() const = 0;
	// Сравнение по массе.
	virtual bool operator== (const IPhysObject& ob) const = 0;
	// Сравнение по массе.
	virtual bool operator< (const IPhysObject& ob) const = 0;
};
// Интерфейс "Отображаемый"
class IPrintable {
public:
	// Отобразить на экране
	// (выводить в текстовом виде параметры фигуры).
	virtual void draw() const = 0;
};
// Интерфейс для классов, которые можно задать через диалог с пользователем.
class IDialogInitiable {
public:
	// Задать параметры объекта с помощью диалога с пользователем.
	virtual void initFromDialog() = 0;
};
// Интерфейс "Класс"
class IBaseCObject {
public:
	// Имя класса (типа данных).
	virtual const std::string classname() const = 0;
	// Размер занимаемой памяти.
	virtual unsigned int size() const = 0;
};

class IFigure : public IGeoFig, public IPhysObject, public IPrintable, 
public IDialogInitiable, public IBaseCObject {
public:

};

class Rectangle : public IFigure {
private:
	const std::string name = "Rectangle";
	double a, b;
	double mass_;
	Vector2D position_;

public:
	double square() const override;
	double perimeter() const override;

	double mass() const override;
	Vector2D position() const override;

	bool operator== (const IPhysObject& ob) const override;
	bool operator< (const IPhysObject& ob) const override;

	void draw() const override;

	void initFromDialog() override;

	const std::string classname() const override;
	unsigned int size() const override;
};

class Circle : public IFigure {
private:
	const std::string name = "Circle";
	double r;
	double mass_;
	Vector2D position_;

public:
	double square() const override;
	double perimeter() const override;

	double mass() const override;
	Vector2D position() const override;

	bool operator== (const IPhysObject& ob) const override;
	bool operator< (const IPhysObject& ob) const override;

	void draw() const override;

	void initFromDialog() override;

	const std::string classname() const override;
	unsigned int size() const override;
};