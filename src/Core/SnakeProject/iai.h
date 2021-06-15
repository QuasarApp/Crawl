#ifndef IAI_H
#define IAI_H

/**
 * @brief The IAI class Is default interface for ai classes.
 * @note example of use :
 * ```cpp
 * class MyAI :public MyControl, public IAI {
 *     void startAI();
 *     void stopAI();
 * }
 * ```
 */
class IAI
{
public:
    IAI();
    virtual ~IAI() = default;

    /**
     * @brief startAI This method must be run ai.
     */
    virtual void startAI() = 0;

    /**
     * @brief stopAI This method must be stop ai.
     */
    virtual void stopAI() = 0;
};

#endif // IAI_H
