#include <algorithm>
#include <bitset>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <math.h>
#include <vector>
#include <set>
#include <sstream>
#include <unordered_map>

using namespace std;

struct Classification
{
	double p_c = 0.0;
	int totalClassDocs = 0;
	int totalWordsInDocs = 0;
	unordered_map<string, int> freqOfWords;
};

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		std::cout << "Format: ./EXECUTABLE TRAINING_INPUT TESTING_INPUT" << endl;
	}

	string input;
	ifstream ifs(argv[1]);
	vector<string> x = {"a", "about", "above", "after", "again", "against", "all", "am", "an", "and", "any", "are", "aren't", "as", "at", "be", "because", "been", "before", "being", "below", "between", "both", "but", "by", "can't", "cannot", "could", "couldn't", "did", "didn't", "do", "does", "doesn't", "doing", "don't", "down", "during", "each", "few", "for", "from", "further", "had", "hadn't", "has", "hasn't", "have", "haven't", "having", "he", "he'd", "he'll", "he's", "her", "here", "here's", "hers", "herself", "him", "himself", "his", "how", "how's", "i", "i'd", "i'll", "i'm", "i've", "if", "in", "into", "is", "isn't", "it", "it's", "its", "itself", "let's", "me", "more", "most", "mustn't", "my", "myself", "no", "nor", "not", "of", "off", "on", "once", "only", "or", "other", "ought", "our", "ours", "ourselves", "out", "over", "own", "same", "shan't", "she", "she'd", "she'll", "she's", "should", "shouldn't", "so", "some", "such", "than", "that", "that's", "the", "their", "theirs", "them", "themselves", "then", "there", "there's", "these", "they", "they'd", "they'll", "they're", "they've", "this", "those", "through", "to", "too", "under", "until", "up", "very", "was", "wasn't", "we", "we'd", "we'll", "we're", "we've", "were", "weren't", "what", "what's", "when", "when's", "where", "where's", "which", "while", "who", "who's", "whom", "why", "why's", "with", "won't", "would", "wouldn't", "you", "you'd", "you'll", "you're", "you've", "your", "yours", "yourself", "yourselves"};
	const char *stopwords[] = {"a", "about", "above", "after", "again", "against", "all", "am", "an", "and", "any", "are", "aren't", "as", "at", "be", "because", "been", "before", "being", "below", "between", "both", "but", "by", "can't", "cannot", "could", "couldn't", "did", "didn't", "do", "does", "doesn't", "doing", "don't", "down", "during", "each", "few", "for", "from", "further", "had", "hadn't", "has", "hasn't", "have", "haven't", "having", "he", "he'd", "he'll", "he's", "her", "here", "here's", "hers", "herself", "him", "himself", "his", "how", "how's", "i", "i'd", "i'll", "i'm", "i've", "if", "in", "into", "is", "isn't", "it", "it's", "its", "itself", "let's", "me", "more", "most", "mustn't", "my", "myself", "no", "nor", "not", "of", "off", "on", "once", "only", "or", "other", "ought", "our", "ours", "ourselves", "out", "over", "own", "same", "shan't", "she", "she'd", "she'll", "she's", "should", "shouldn't", "so", "some", "such", "than", "that", "that's", "the", "their", "theirs", "them", "themselves", "then", "there", "there's", "these", "they", "they'd", "they'll", "they're", "they've", "this", "those", "through", "to", "too", "under", "until", "up", "very", "was", "wasn't", "we", "we'd", "we'll", "we're", "we've", "were", "weren't", "what", "what's", "when", "when's", "where", "where's", "which", "while", "who", "who's", "whom", "why", "why's", "with", "won't", "would", "wouldn't", "you", "you'd", "you'll", "you're", "you've", "your", "yours", "yourself", "yourselves"};
	set<string> setOfStopWords(stopwords, stopwords + x.size());


	int totalNumDocs = 0;
	Classification **classes = new Classification*[16];
	for(int i = 0; i < 16; i++)
	{
		classes[i] = new Classification();
	}
	vector<int> countDocs(16, 0);
	vector<string> combinedDocs(16, "");

	/*---LEARNING PHASE---*/

	//Iterate through docs to find number of occurences for each document, 
	//also training phase (stores word freq in set for each class)

	int start_learn = clock();
	while(getline(ifs, input))
	{
		int ilen = input.length();
		if(input.substr(ilen - 2, 1) == "1")
		{
			int docNum = stoi(input.substr(ilen - 2));
			istringstream stream(input);
			string word;
			while(stream >> word)
			{
				if(setOfStopWords.count(word) == 0)
				{
					combinedDocs[docNum] += word;
					classes[docNum]->totalWordsInDocs++;
					if(classes[docNum]->freqOfWords.find(word) == classes[docNum]->freqOfWords.end())
					{
						classes[docNum]->freqOfWords.insert(pair<string, int>(word, 1));
					}
					else
					{
						classes[docNum]->freqOfWords[word]++;
					}
				}
			}
			classes[docNum]->totalClassDocs++;
			countDocs[docNum]++;
			totalNumDocs++;
		}
		else
		{
			int docNum = stoi(input.substr(ilen - 1));
			istringstream stream(input);
			string word;
			while(stream >> word)
			{
				if(setOfStopWords.count(word) == 0)
				{
					combinedDocs[docNum] += word;
					classes[docNum]->totalWordsInDocs++;
					if(classes[docNum]->freqOfWords.find(word) == classes[docNum]->freqOfWords.end())
					{
						classes[docNum]->freqOfWords.insert(pair<string, int>(word, 1));
					}
					else
					{
						classes[docNum]->freqOfWords[word]++;
					}
				}
			}
			classes[docNum]->totalClassDocs++;
			countDocs[docNum]++;
			totalNumDocs++;
		}
	}

	for(int i = 1; i < 16; i++)
	{
		classes[i]->p_c = double(classes[i]->totalClassDocs) / double(totalNumDocs);
	}

	int stop_learn = clock();
	int learnTime = ceil((stop_learn - start_learn) / double(CLOCKS_PER_SEC));

	ifs.close();

	/*---LEARNING PHASE---*/

	/*---TRAINING DATASET ---*/
	//store each word in a set and iterate through each element in set 
	//to determine the probability of each class, using the Naive Bayes Classifier.
	//Also, store expected document answer for accuracy comparison.

	ifstream ifstrain(argv[1]);
	unordered_map<string, int> trainingInput;
	vector<int> expectedTrainDocs;
	vector<int> estimatedTrainDocs;
	string trainInput;

	while(getline(ifstrain, trainInput))
	{
		int ilen = trainInput.length();
		if(trainInput.substr(ilen - 2, 1) == "1")
		{
			int docNum = stoi(trainInput.substr(ilen - 2));
			istringstream stream(trainInput);
			string word;
			while(stream >> word)
			{
				if(setOfStopWords.count(word) == 0)
				{
					if(trainingInput.find(word) == trainingInput.end())
					{
						trainingInput.insert(pair<string, int>(word, 1));
					}
					else
					{
						trainingInput[word]++;
					}		
				}	
			}
			expectedTrainDocs.push_back(docNum);
		}
		else
		{
			int docNum = stoi(trainInput.substr(ilen - 1));
			istringstream stream(trainInput);
			string word;
			while(stream >> word)
			{
				if(setOfStopWords.count(word) == 0)
				{
					if(trainingInput.find(trainInput) == trainingInput.end())
					{
						trainingInput.insert(pair<string, int>(word, 1));
					}
					else
					{
						trainingInput[word]++;
					}		
				}	
			}
			expectedTrainDocs.push_back(docNum);
		}
		
		//Go through each word in set and estimate prob of each class
		//Also, store the label after calculating

		vector<double> probClasses(16, 0.0);
		double maxProb = 0.0;
		int assignedDoc = 0;
		for(int i = 1; i < 16; i++)
		{
			double totalProduct = log(classes[i]->p_c + 1);
			for(auto& x : trainingInput)
			{
				if(classes[i]->freqOfWords.find(x.first) == classes[i]->freqOfWords.end())
				{
					totalProduct += log(double(1) / double(classes[i]->totalWordsInDocs + x.second) + 1);
				}
				else
				{
					if(classes[i]->freqOfWords[x.first] > 1 || classes[i]->freqOfWords[x.first] == x.second)
					{
						totalProduct += log(double(classes[i]->freqOfWords[x.first]) / double(classes[i]->totalWordsInDocs + abs(classes[i]->freqOfWords[x.first] - x.second)) + 1);
					}
				}
				totalProduct += log(x.second + 1);
			}
			if(maxProb < totalProduct)
			{
				maxProb = totalProduct;
				assignedDoc = i;
			}
		}

		estimatedTrainDocs.push_back(assignedDoc);
		trainingInput.clear();
	}

	ifstrain.close();
	
	int numTrainCorrect = 0;
	for(int i = 0; i < expectedTrainDocs.size(); i++)
	{
		if(expectedTrainDocs[i] == estimatedTrainDocs[i])
		{
			numTrainCorrect++;
		}
	}

	/*---TESTING DATASET ---*/
	//store each word in a set and iterate through each element in set 
	//to determine the probability of each class, using the Naive Bayes Classifier.
	//Also, store expected document answer for accuracy comparison.

	string testInput;
	ifstream ifstest(argv[2]);
	unordered_map<string, int> testingInput;
	vector<int> expectedTestDocs;
	vector<int> estimatedTestDocs;

	int start_train = clock();
	while(getline(ifstest, testInput))
	{
		int ilen = testInput.length();
		if(testInput.substr(ilen - 2, 1) == "1")
		{
			int docNum = stoi(testInput.substr(ilen - 2));
			istringstream stream(testInput);
			string word;
			while(stream >> word)
			{
				if(setOfStopWords.count(word) == 0)
				{
					if(testingInput.find(word) == testingInput.end())
					{
						testingInput.insert(pair<string, int>(word, 1));
					}
					else
					{
						testingInput[word]++;
					}		
				}	
			}
			expectedTestDocs.push_back(docNum);
		}
		else
		{
			int docNum = stoi(testInput.substr(ilen - 1));
			istringstream stream(testInput);
			string word;
			while(stream >> word)
			{
				if(setOfStopWords.count(word) == 0)
				{
					if(testingInput.find(trainInput) == testingInput.end())
					{
						testingInput.insert(pair<string, int>(word, 1));
					}
					else
					{
						testingInput[word]++;
					}		
				}	
			}
			expectedTestDocs.push_back(docNum);
		}
		
		//Go through each word in set and estimate prob of each class
		//Also, store the label after calculating

		vector<double> probClasses(16, 0.0);
		double maxProb = 0.0;
		int assignedDoc = 0;
		for(int i = 1; i < 16; i++)
		{
			double totalProduct = log(classes[i]->p_c + 1);
			for(auto& x : testingInput)
			{
				if(classes[i]->freqOfWords.find(x.first) == classes[i]->freqOfWords.end())
				{
					totalProduct += log(double(1) / double(classes[i]->totalWordsInDocs + x.second) + 1);
				}
				else
				{
					if(classes[i]->freqOfWords[x.first] > 1 || classes[i]->freqOfWords[x.first] == x.second)
					{
						totalProduct += log(double(classes[i]->freqOfWords[x.first]) / double(classes[i]->totalWordsInDocs + abs(classes[i]->freqOfWords[x.first] - x.second)) + 1);
					}
				}
			}
			if(maxProb < totalProduct)
			{
				maxProb = totalProduct;
				assignedDoc = i;
			}
		}
		cout << assignedDoc << endl;
		estimatedTestDocs.push_back(assignedDoc);
		testingInput.clear();
	}

	int stop_train = clock();
	int trainTime = ceil((stop_train - start_train) / double(CLOCKS_PER_SEC));

	ifstest.close();
	
	int numTestCorrect = 0;
	for(int i = 0; i < expectedTestDocs.size(); i++)
	{
		if(expectedTestDocs[i] == estimatedTestDocs[i])
		{
			numTestCorrect++;
		}
	}
	
	cout << learnTime << " seconds (training)" << endl;
	cout << trainTime << " seconds (labeling)" << endl;
	cout << setprecision(3) << double(numTrainCorrect) / double(expectedTrainDocs.size()) << " (training)" << endl;
	cout << setprecision(3) << double(numTestCorrect) / double(expectedTestDocs.size()) << " (testing)" << endl;
	return 0;
}