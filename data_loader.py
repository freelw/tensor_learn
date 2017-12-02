# -*- coding: UTF-8 -*- 
import codecs

train_file_name = './train_data/train/demo/train.txt'
test_file_name = './train_data/test/demo/test.txt'

def get_hot1_vec(height, index):
    ret = []
    for i in xrange(height):
        if i == index:
            ret.append(1)
        else:
            ret.append(0)
    return ret

def load_data(file_name, width, height):
    ret_x = []
    ret_y = []
    with codecs.open(file_name, 'r', 'utf-8') as f:
        lines = f.readlines()
        for line in lines:
            tag = int(line[0])
            btar = bytearray(line, 'utf-8')
            ret_x.append(list(btar[2:2+width]))
            ret_y.append(get_hot1_vec(height, tag))
    return ret_x, ret_y

def load_train_data(width, height):
    return load_data(train_file_name, width, height)

def load_test_data(width, height):
    return load_data(test_file_name, width, height)

if '__main__' == __name__:
    print load_train_data(1, 6)
    print load_test_data(1, 6)