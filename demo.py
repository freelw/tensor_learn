# -*- coding: UTF-8 -*- 

WIDTH = 50
HEIGHT = 6

import data_loader

def get_empty(cnt, width):
    ret = []
    for i in xrange(cnt):
        tmp = []
        for j in xrange(width):
            tmp.append(0)
        ret.append(tmp)
    return ret

def get_train_xy():
    return data_loader.load_train_data(WIDTH, HEIGHT)
    #return get_empty(10, WIDTH), get_empty(10, HEIGHT)

def get_test_xy():
    return data_loader.load_test_data(WIDTH, HEIGHT)
    #return get_empty(10, WIDTH), get_empty(10, HEIGHT)
    
import tensorflow as tf
x = tf.placeholder(tf.float32, [None, WIDTH])
W = tf.Variable(tf.zeros([WIDTH,HEIGHT]))
b = tf.Variable(tf.zeros([HEIGHT]))
y = tf.nn.softmax(tf.matmul(x,W) + b)
y_ = tf.placeholder("float", [None,HEIGHT])
cross_entropy = -tf.reduce_sum(y_*tf.log(y))
train_step = tf.train.GradientDescentOptimizer(0.01).minimize(cross_entropy)
init = tf.global_variables_initializer()
sess = tf.Session()
sess.run(init)

train_x, train_y = get_train_xy()
sess.run(train_step, feed_dict={x: train_x, y_: train_y})

correct_prediction = tf.equal(tf.argmax(y,1), tf.argmax(y_,1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction, "float"))

test_x, test_y = get_test_xy()
print sess.run(accuracy, feed_dict={x: test_x, y_: test_y})