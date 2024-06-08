/**
 * @file quack.cpp
 * Implementation of the Quack class.
 *
 */

template <class T>

Quack<T>::Quack()
{
    vector<T> d(1);

    data = d;
    n1 = 0;
    n2 = 0;
}

/**
 * Adds the parameter object to the right of the Quack.
 *
 * @param newItem object to be added to the Quack.
 */
template <class T>
void Quack<T>::push_right(T newItem)
{
    int s = data.size();
    if (n2 < s)
    {
        data[n2] = newItem;
    }
    else
    {
        data.push_back(newItem);
    }

    n2++;
}

/**
 * Removes the object at the left of the Quack, and returns it to the
 * caller.
 *
 * See .h file for implementation notes.
 *
 * @return The item that used to be at the left of the Quack.
 */
template <class T>
T Quack<T>::pop_left()
{

    T popl = data[n1];
    n1++;

    if (n2 - n1 <= n1)
    {
        vector<T> d(n2 - n1);

        for (int i = 0; i < n2 - n1; i++)
        {
            d[i] = data[n1 + i];
        }
        n2 = n2 - n1;
        n1 = 0;
        data = d;
    }

    return popl;
}
/**
 * Removes the object at the right of the Quack, and returns it to the
 * caller.
 *
 * @return The item that used to be at the right of the Quack.
 */
template <class T>
T Quack<T>::pop_right()
{
    T popr = data[n2 - 1];
    n2--;

    if (n2 - n1 <= n1)
    {
        vector<T> d(n2 - n1);

        for (int i = 0; i < n2 - n1; i++)
        {
            d[i] = data[n1 + i];
        }
        n2 = n2 - n1;
        n1 = 0;
        data = d;
    }

    return popr;
}

/**
 * Finds the object at the left of the Quack, and returns it to the
 * caller. Unlike pop_left(), this operation does not alter the quack.
 *
 * @return The item at the front of the quack.
 */
template <class T>
T Quack<T>::peekL()
{

    T popl = data[n1];
    return popl;
}

/**
 * Finds the object at the right of the Quack, and returns it to the
 * caller. Unlike pop_right(), this operation does not alter the quack.
 *
 * @return the value of The item at the right of the quack.
 */
template <class T>
T Quack<T>::peekR()
{
    T popr = data[n2 - 1];
    return popr;
}

/**
 * Determines if the Quack is empty.
 *
 * @return bool which is true if the Quack is empty, false otherwise.
 */
template <class T>
bool Quack<T>::is_empty() const
{
    return n1 == n2;
}
