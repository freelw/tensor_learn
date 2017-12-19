# -*- coding: UTF-8 -*- 
import codecs

train_file_name = './train_data/train/demo/train.txt'
#train_file_name = './train_data/train/demo/hex'
test_file_name = './train_data/test/demo/test.txt'
window_width = 10
magic_num = 65535
mod_num = 10000001

def get_hot1_vec(height, index):
    ret = []
    for i in xrange(height):
        if i == index:
            ret.append(1)
        else:
            ret.append(0)
    return ret

def safe_div(a, b):
    if 0 == b:
        return 0
    return a/b

def hash(arr):
    ret = 0
    for item in arr:
        ret += item
        ret *= magic_num
        ret %= mod_num
    return ret

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
                _x = list(btar[2:2+width+window_width])

                x = []
                for i in xrange(width):
                    hash_val = hash(_x[i:i+width])
                    x.append(hash_val)

                for i in xrange(width-len(x)):
                    x.append(0)

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