//
// Created by fs on 2/24/20.
//

#pragma once

#include "list.hpp"
#include "mutex.hpp"

namespace PubSub {

typedef void (*CallbackPtr)(void *);

struct Callback : public ListNode<Callback *> {
  CallbackPtr callback_ptr_ = nullptr;
  void *callback_data_ = nullptr;
};

// The template is used only to define unique global variables in the header
// file.
template <class Type>
struct StaticValue {
  static Type value;
};

template <class Type>
Type StaticValue<Type>::value;

template <typename T>
class Node {
 protected:
  // The following data are unique in the same topic
  static T data_;
  static unsigned generation_;
  static List<Callback *> callbacks_;
  static Mutex &lock_;
};

template <typename T>
T Node<T>::data_;

template <typename T>
unsigned Node<T>::generation_;

template <typename T>
List<Callback *> Node<T>::callbacks_;

template <typename T>
PubSub::Mutex &Node<T>::lock_ = StaticValue<Mutex>::value;

}  // namespace PubSub
