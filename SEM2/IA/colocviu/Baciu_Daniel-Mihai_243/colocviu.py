#!/usr/bin/env python
# coding: utf-8

# In[ ]:


# jupyter nbconvert --to python ex1.ipynb


# In[85]:


import numpy as np
import matplotlib

from sklearn.feature_extraction.text import CountVectorizer, TfidfTransformer
from sklearn.kernel_ridge import KernelRidge
from sklearn.model_selection import train_test_split


# In[60]:


path = "./varianta2/"
data_txt = np.load(path + "train_data.npy")
data_labels = np.load(path + "train_labels.npy")
test_txt = np.load(path + "test_data.npy")


# In[76]:


train_txt, validation_txt, train_labels, validation_labels = train_test_split(data_txt, data_labels, test_size=0.1)


# In[77]:


def similarity(string1, string2, n_gram) :
    k = 0

    for i in range(len(string1) - n_gram - 1) :

        if string1[i : i + n_gram] in string2 :

            k += 1

    return k


# In[78]:


# for i in range(len(data_images)):
#     for j in range(i + 1, len(data_images)) :
#         print(similarity(data_images[i], data_images[j], 4))


# In[79]:


# similarity("ananas copt", "banana verde", 4)


# In[80]:


def classifica_imaginea(txt_train, labeluri_train, string_pentru_clasificat, no_of_neigh = 1, n_gram_dimension = 4) :

    distante = np.array([similarity(x, string_pentru_clasificat, n_gram_dimension) for x in txt_train])

    indici_sortati = np.argsort(distante)

    indici_sortati = indici_sortati[ :no_of_neigh]

    preziceri = labeluri_train[indici_sortati]

    d = {}

    d[1] = d[-1] = 0

    for x in preziceri :
        d[x] += 1

    if d[1] >= d[-1] :
        return 1
    return -1


# In[81]:


# d = {}
# for x in train_labels :
#     if x not in d :
#         d[x] = 0
#     d[x] += 1
#
# print(d)


# In[83]:


# for no_of_neig in [3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25] :
for no_of_neig in range(100) :

    # for n_gram in [3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23] :

    n_gram = 8 # l-am luat din cerinta de la 1

    predictii = []

    for img in validation_txt:

        predictii.append(classifica_imaginea(train_txt, train_labels, img, no_of_neig, n_gram))

    predictii = np.array(predictii)

    # print(f"Valoarea de prezicere pentru \tnr vecini = \t{no_of_neig} \t si n_gram = \t{n_gram} \teste = \t{(validation_labels == predictii).mean()}")
    print(f"Valoarea de prezicere pentru \tnr vecini = \t{no_of_neig} \teste = \t{(validation_labels == predictii).mean()}")

print("\n--------------------------------------------------------------------------------\n")


# In[69]:


def write_output_file(predictii, varianta):
    f = open("Baciu_Daniel-Mihai_243_" + varianta + ".txt", "w")
    f.write("label\n")
    for i in range(len(predictii)):
        f.write(f"{predictii[i]}\n")


# In[70]:


predictii = []

for txt in test_txt:

    predictii.append(classifica_imaginea(data_txt, data_labels, txt, no_of_neigh=10, n_gram_dimension=8))

write_output_file(predictii, "subiect_2_solutie_1")


# In[75]:





# In[ ]:





# In[71]:


kernel_matrix_train = np.array([np.array([similarity(data_txt[i], data_txt[j], 8) for i in range(len(data_txt))]) for j in range(len(data_txt))])

kernel_matrix_test = np.array([np.array([similarity(test_txt[i], data_txt[j], 8) for i in range(len(test_txt))]) for j in range(len(data_txt))])


# In[73]:


print(kernel_matrix_test.shape)


# In[95]:


kernel_mtx_train = np.array([np.array([similarity(train_txt[i], train_txt[j], 8) for i in range(len(train_txt))]) for j in range(len(train_txt))])
kernel_mtx_validation = np.array([np.array([similarity(train_txt[i], validation_txt[j], 8) for i in range(len(train_txt))]) for j in range(len(validation_txt))])


# In[96]:





# In[112]:


for alpha in [0.4, 0.7, 1.1, 1.3, 1.5, 1.9, 2.1, 2.3, 2.5, 2.7, 2.9, 3.1, 3.5, 3.9, 4.3, 4.7, 5.5, 6.1, 6.9, 7.5, 8.1, 8.9, 9.3]:

    model = KernelRidge(kernel="precomputed", alpha=alpha)

    model.fit(kernel_mtx_train, train_labels)

    etichete = model.predict(kernel_mtx_validation)

    predictii = []

    for x in etichete :
        if x <= 0 :
            predictii.append(-1)
        else :
            predictii.append(1)

    print(f"valoarea de predicti pt alpha = {alpha} este {(np.array(predictii) == validation_labels).mean()}")


# In[115]:


k = 1
for alpha in [7.5, 8.9, 9.3]:

    model = KernelRidge(kernel="precomputed", alpha=alpha)

    model.fit(kernel_mtx_train, train_labels)

    etichete = model.predict(kernel_mtx_validation)

    predictii = []

    for x in etichete :
        if x <= 0 :
            predictii.append(-1)
        else :
            predictii.append(1)

    print(f"valoarea de predicti pt alpha = {alpha} este {(np.array(predictii) == validation_labels).mean()}")

    write_output_file(predictii, f"subiect_4_solutie{k}")
    k += 1


# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:




