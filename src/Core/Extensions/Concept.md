# Extension concept

The extension it is separate module class with custom function.

## How to use 

1. Create own child class from IRender interface.
2. Override the IRender::render method of base interface
3. Check compatibility betwin this type and requred type using the IRender::checkminimumRequariedType method.
4. In the render method using dynamic_cast operator get neede interface of class object.
5. Implement needed functions for object.


## Example:

Movable object header:

```cpp

class CRAWL_EXPORT MovableObject: public virtual IRender
{

public:
    MovableObject();

    void render(unsigned int tbfMsec) override;

    const QVector3D &movableVector() const;

    void setMovableVector(const QVector3D &newMovableVector);

    float angularVelocity() const;

    void setAngularVelocity(float newAngularVelocity);

    float breakingForce() const;

    void setBreakingForce(float newBreakingForce);

private:
    QVector3D _movableVector;
    QVector3D _currentMovableVector;

    float _angularVelocity = 0;
    float _breakingForce = 0;
};
```

Movable object source:

```cpp
MovableObject::MovableObject()
{

}

void MovableObject::render(unsigned int tbfMsec) {
    auto _this = checkminimumRequariedType<IWorldItem>();

    // get object center position
    QVector3D currentPosition = _this->position();

    // move object to vector
    currentPosition += (_currentMovableVector * (tbfMsec / 1000.0));
    _this->setposition(currentPosition);

    // calc temp vector betvin user moveble vector and real moveble vector
    QVector3D tempVector = _movableVector - _currentMovableVector ;

    // calc change on this iteration for new moveble vector
    float delta = std::min(_angularVelocity * (tbfMsec / 1000.0), static_cast<double>(tempVector.length()));

    // resize temp vector for calc changes of the movableVector
    tempVector = tempVector.normalized() * delta;

    // recalc new currentMovable vector (applay changes)
    _currentMovableVector += tempVector;

    float newMovableVectorLength = std::max(_movableVector.length() - (_breakingForce * (tbfMsec / 1000.0)), 0.0);

    // update movable vector
    _movableVector = _movableVector.normalized() * newMovableVectorLength;

}

const QVector3D &MovableObject::movableVector() const  {
    return _movableVector;
}

void MovableObject::setMovableVector(const QVector3D &newMovableVector) {
    _movableVector = newMovableVector;
}

float MovableObject::angularVelocity() const {
    return _angularVelocity;
}

void MovableObject::setAngularVelocity(float newAngularVelocity) {
    _angularVelocity = newAngularVelocity;
}

float MovableObject::breakingForce() const {
    return _breakingForce;
}

void MovableObject::setBreakingForce(float newBreakingForce) {
    _breakingForce = newBreakingForce;
}

```
