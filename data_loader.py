# -*- coding: UTF-8 -*- 
import codecs

train_file_name = './train_data/train/demo/train.txt'
#train_file_name = './train_data/train/demo/hex'
test_file_name = './train_data/test/demo/test.txt'

def get_hot1_vec(height, index):
    ret = []
    for i in xrange(height):
        if i == index:
            ret.append(1)
        else:
            ret.append(0)
    return ret

def calc_space_count(line):
    ret = 0
    for ch in line:
        if ' ' == ch:
            ret += 1
    return ret

def safe_div(a, b):
    if 0 == b:
        return 0
    return a/b

def load_data(file_name, width, height):
    ret_x = []
    ret_y = []
    line_no = 1
    with codecs.open(file_name, 'r', 'utf-8') as f:
        lines = f.readlines()
        for line in lines:
            try:
                tag = int(line[0])
                btar = bytearray(line, 'utf-8')
                x = list(btar[2:2+width])
                for i in xrange(width-len(x)):
                    x.append(0)
                #space_count = calc_space_count(line[2:])
                #len_btar = len(btar)
                #print space_count, len_btar
                #x.append(space_count)
                #x.append(len(btar))
                #x.append(safe_div(space_count, len_btar))
                ret_x.append(x)
                ret_y.append(get_hot1_vec(height, tag))
            except Exception, e:
                print '--------------', line_no, e
            line_no += 1
    return ret_x, ret_y

def load_train_data(width, height):
    return load_data(train_file_name, width, height)

def load_test_data(width, height):
    return load_data(test_file_name, width, height)

if '__main__' == __name__:
    print load_train_data(1, 6)
    print load_test_data(1, 6)