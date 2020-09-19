import numpy as np
import pickle
import re
import math
from os import listdir
from os.path import isfile, join
import seaborn as sn
import matplotlib.pyplot as plt
import matplotlib as mpl
import pandas as pd
import itertools
import os
from sklearn.metrics import confusion_matrix


def plot_confusion_matrix(cm, classes, normalize=False, cmap="Blues", png_output=None, show=True):
	"""
	This function prints and plots the confusion matrix.
	Normalization can be applied by setting `normalize=True`.
	"""
	if normalize:
		cm = cm.astype('float') / cm.sum(axis=1)[:, np.newaxis]
		title='Normalized confusion matrix'
	else:
		title='Confusion matrix'

	# Calculate chart area size
	leftmargin = 0.5 # inches
	rightmargin = 0.5 # inches
	categorysize = 0.5 # inches
	figwidth = leftmargin + rightmargin + (len(classes) * categorysize)           

	f = plt.figure(figsize=(figwidth, figwidth))

	# Create an axes instance and ajust the subplot size
	ax = f.add_subplot(111)
	ax.set_aspect(1)
	f.subplots_adjust(left=leftmargin/figwidth, right=1-rightmargin/figwidth, top=0.94, bottom=0.1)

	res = ax.imshow(cm, interpolation='nearest', cmap=cmap)

	#plt.title(title)
	plt.colorbar(res)
	ax.set_xticks(range(len(classes)))
	ax.set_yticks(range(len(classes)))
	ax.set_xticklabels(classes, rotation=45, ha='right')
	ax.set_yticklabels(classes)

	fmt = '.2f' if normalize else 'd'
	thresh = cm.max() / 2.
	for i, j in itertools.product(range(cm.shape[0]), range(cm.shape[1])):
		ax.text(j, i, format(cm[i, j], fmt),
				horizontalalignment="center",
				color="white" if cm[i, j] > thresh else "black")

	# plt.tight_layout()
	plt.ylabel('True label')
	plt.xlabel('Predicted label')

	if png_output is not None:
		os.makedirs(png_output, exist_ok=True)
		f.savefig(os.path.join(png_output,'confusion_matrix.png'), bbox_inches='tight')

	if show:
		plt.show()
		plt.close(f)
	else:
		plt.close(f)


label=np.asarray(['Arreter','Appeler','Saluer','Venir','Repartir','Pointer','Autre'])

cmap = mpl.cm.Blues(np.linspace(0,1,100))
cmap = mpl.colors.ListedColormap(cmap[0:90,:-1])

def confusion_matrix_as_it_should(y_argmax, evaluation, label=None, column_tilt=30, line_tilt=0, cmap="Blues", cm=None):

  # this will re order according to the labels
  # use percentage instead of number of TP
  # uses a good colormap
  # tilts the labels

	if cm==None:
		if label!=None:
			labelindex=np.arange(len(label))
			replacer = dict(zip(labelindex, label))
			numbers_list = y_argmax.tolist()
			y_argmax = np.array(list(map(replacer.get, numbers_list, numbers_list)))
			numbers_list = evaluation.tolist()
			evaluation = np.array(list(map(replacer.get, numbers_list, numbers_list)))
		#do this for normalised:   .apply(lambda r: 100*(r/r.sum())//1/100, axis=1)
		confusion = pd.crosstab(y_argmax,evaluation ,rownames=['Cible'], colnames=['Prédiction'])
    #results = confusion_matrix(y_argmax, evaluation)
	
	else: # if CM is ready

		confusion = pd.DataFrame(cm, index= label, columns= label )
		# need from 

		#print(a)
		conf = pd.crosstab(confusion[:][0],confusion[0][:], rownames=['Cible'], colnames=['Prédiction']).apply(lambda r: r/r.sum(), axis=1)
		print(cm)
	if label!=None:
		confusion = confusion.reindex(label, axis=0)
		confusion = confusion.reindex(label, axis=1)


	c = sn.heatmap(confusion, annot=True, cmap=cmap)
	if label!=None:
		c.set_xticklabels(rotation=column_tilt, labels=label )
		c.set_yticklabels(rotation= line_tilt, labels=label )
	
	plt.show()

	return confusion






files = [f for f in listdir("LOOCV") if isfile(join("LOOCV",f))]
datasets = ["Florence_x","Florence_y","KARD_x","KARD_y","CAD60_120_13_x","CAD60_120_13_y","UTKinect_x","UTKinect_y"]
datasets = ["UTKinect_bis"]


#datasets = ["archi1","archi2","archi3","archi4", "archi_", "cnnlstm"]


archi = ""
archi = "cnn_"
# KARD now


for dataset in datasets:
	dataset=archi+dataset
	print(dataset)
	evaluation_list = []
	y_argmax_list = []
	y_test_np_list = []
	results_list = []
	confusion_list = []
	hist_list = []

	evaluation_list = np.array(evaluation_list)
	y_argmax_list = np.array(y_argmax_list)
	y_test_np_list = np.array(y_test_np_list)
	results_list = np.array(results_list)
	confusion_list = np.array(confusion_list)
	evaluation =[]
	for f in files:
		if "_s1_" in f or "_s01_" in f:
			if dataset in f and "eval" in f:
				p = open("LOOCV/"+f,"rb")
				evaluation_list = pickle.load(p)
			if dataset in f and "y_argmax" in f:
				p = open("LOOCV/"+f,"rb")
				y_argmax_list = pickle.load(p)
			if dataset in f and "y_test_np" in f:
				p = open("LOOCV/"+f,"rb")
				y_test_np_list = pickle.load(p)
				pass				
			if dataset in f and "results" in f:
				p = open("LOOCV/"+f,"rb")
				results = pickle.load(p)	
				#print(results)				
				results_list = results
			if dataset in f and "confusion" in f:
				p = open("LOOCV/"+f,"rb")
				conf = pickle.load(p)
				#print(conf)
				confusion_list = conf
			if dataset in f and "hist" in f:
				p = open("LOOCV/"+f,"rb")
				h = pickle.load(p)
				hist_list.append(h)
				m = np.array(h['val_loss']).argmin()
				print(1,h["val_accuracy"][m])


	for i in range(2,11):
		for f in files:
			if "_s"+str(i)+"_" in f or "_s0"+str(i)+"_" in f:
				if dataset in f and "eval" in f:
					p = open("LOOCV/"+f,"rb")
					evaluation_list = np.concatenate((evaluation_list,pickle.load(p)))
				if dataset in f and "y_argmax" in f:
					p = open("LOOCV/"+f,"rb")
					y_argmax_list = np.concatenate((y_argmax_list,pickle.load(p)))
				if dataset in f and "y_test_np" in f:
					#p = open("LOOCV/"+f,"rb")
					#y_test_np_list = np.concatenate((y_test_np_list,pickle.load(p)))
					pass				
				if dataset in f and "results" in f:
					p = open("LOOCV/"+f,"rb")
					results= pickle.load(p)	
					#print(results)
					#results_list = np.concatenate((results_list,results), )
				if dataset in f and "confusion" in f:
					p = open("LOOCV/"+f,"rb")
					conf = pickle.load(p)
					#print(conf)
					#confusion_list = np.concatenate((confusion_list,pickle.load(p)))
				if dataset in f and "hist" in f:
					p = open("LOOCV/"+f,"rb")
					h = pickle.load(p)
					hist_list.append(h)
					m = np.array(h['val_loss']).argmin()
					print(i,h["val_accuracy"][m])

	#print(evaluation_list.shape)
	#print(y_argmax_list.shape)


	#confusion_matrix_as_it_should(y_argmax_list,evaluation_list,cmap=cmap)



	#	card only:
	# y_argmax_list = np.where(y_argmax_list==8,7,y_argmax_list)
	# y_argmax_list = np.where(y_argmax_list==9,8,y_argmax_list)
	# y_argmax_list = np.where(y_argmax_list==10,9,y_argmax_list)
	# y_argmax_list = np.where(y_argmax_list==11,10,y_argmax_list)
	# y_argmax_list = np.where(y_argmax_list==12,11,y_argmax_list)
	# y_argmax_list = np.where(y_argmax_list==15,12,y_argmax_list)
	# evaluation_list = np.where(evaluation_list==8,7,evaluation_list)
	# evaluation_list = np.where(evaluation_list==9,8,evaluation_list)
	# evaluation_list = np.where(evaluation_list==10,9,evaluation_list)
	# evaluation_list = np.where(evaluation_list==11,10,evaluation_list)
	# evaluation_list = np.where(evaluation_list==12,11,evaluation_list)
	# evaluation_list = np.where(evaluation_list==15,12,evaluation_list)

	evaluation_list=evaluation_list+1
	y_argmax_list=y_argmax_list+1

	# cm = pd.crosstab(y_argmax_list,evaluation_list ,rownames=['Cible'], colnames=['Prédiction'])
	#cm = confusion_matrix(y_argmax_list,evaluation_list)
	#cad_label= ["immobile","parler au téléphone","ecrire sur un tableau","boir de l'eau","se rincer la bouche","se brosser les dents","porter lentilles de contact","parler sur canapé","se détendre sur canapé","cuisiner (hacher)","cuisiner (remuer)","ouvrir contenant pillule","travailler sur ordinateur"]
	
	#plot_confusion_matrix(cm, np.arange(1,14), normalize=True)
	confusion_matrix_as_it_should(y_argmax_list,evaluation_list)
	
	
	#print(results)

	val=0
	best=0
	worst=999999999

	prec=0
	best_p=0
	worst_p=999999999

	rec=0
	best_r=0
	worst_r=999999999

	f1=0
	best_f=0
	worst_f=999999999
	for h in hist_list:
		m = np.array(h['val_loss']).argmin()
		val+=h["val_accuracy"][m]
		if best < h["val_accuracy"][m]:
			best = h["val_accuracy"][m]
		if worst > h["val_accuracy"][m]:
			worst = h["val_accuracy"][m]

		prec+=h["val_precision"][m]
		if best_p < h["val_precision"][m]:
			best_p = h["val_precision"][m]
		if worst_p > h["val_precision"][m]:
			worst_p = h["val_precision"][m]

		rec+=h["val_recall"][m]
		if best_r < h["val_recall"][m]:
			best_r = h["val_recall"][m]
		if worst_r > h["val_recall"][m]:
			worst_r = h["val_recall"][m]

		f1+=h["val_f_measure"][m]
		if best_f < h["val_f_measure"][m]:
			best_f = h["val_f_measure"][m]
		if worst_f > h["val_f_measure"][m]:
			worst_f = h["val_f_measure"][m]

	print("loss",h['val_loss'][m])
	print("\tmean\t",val/len(hist_list))
	print("\tbest\t",best)
	print("\tworst\t",worst)
	print()
	print("\tmean\t",prec/len(hist_list))
	print("\tbest_p\t",best_p)
	print("\tworst_p\t",worst_p)
	print()
	print("\tmean\t",rec/len(hist_list))
	print("\tbest_r\t",best_r)
	print("\tworst_r\t",worst_r)
	print()
	print("\tmean\t",f1/len(hist_list))
	print("\tbest_f\t",best_f)
	print("\tworst_f\t",worst_f)
	print()

#hist_mean = np.array(hist_list).mean(axis=0)


#print(hist_mean['val_accuracy'][-1])
# no idea how now...



