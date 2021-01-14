#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <array>
using namespace std;
 
typedef array<pair<char, double>, 26> Arr;
 
class Vigenere 
{
private:
  Arr freqArr;
  array<double, 26> targets;
  array<double, 26> sorted;
 
  // Update the frequency array
  Arr& frequency(const string& ciphertext) 
  {
    for (char c = 'A'; c <= 'Z'; ++c)
      freqArr[c - 'A'] = make_pair(c, 0);
 
    for (size_t i = 0; i < ciphertext.size(); ++i)
      freqArr[ciphertext[i] - 'A'].second++;
 
    return freqArr;
  }
 
  double correlation(const string& ciphertext) 
  {
    double result = 0.0;
    frequency(ciphertext);

    sort(freqArr.begin(), freqArr.end(), [](pair<char, double> u, pair<char, double> v)->bool
      { return u.second < v.second; });
 
    for (size_t i = 0; i < 26; ++i)
      result += freqArr[i].second * sorted[i];
 
    return result;
  }
 
public:
  Vigenere(const array<double, 26>& targetFreqs) 
  {
    targets = targetFreqs;
    sorted = targets;
    sort(sorted.begin(), sorted.end());
  }
 
  pair<string, string> decrypt(string ciphertext) 
  {
    string cipher;
    for (size_t i = 0; i < ciphertext.size(); ++i) 
    {
      if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') 
        cipher += ciphertext[i];
      
      else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
        cipher += ciphertext[i] + 'A' - 'a';
      }
    }
 
    size_t bestLength = 0;
    double bestCorr;
 
    for (size_t i = 2; i < cipher.size() / 20; ++i) 
    {
      vector<string> pieces(i);
      for (size_t j = 0; j < cipher.size(); ++j)
        pieces[j % i] += cipher[j];
 
      double corr = -0.5*i;
      for (size_t j = 0; j < i; ++j)
        corr += correlation(pieces[j]);
 
      if (corr > bestCorr) 
      {
        bestLength = i;
        bestCorr = corr;
      }
    }
 
    vector<string> pieces(bestLength);
    for (size_t i = 0; i < cipher.size(); ++i)
      pieces[i % bestLength] += cipher[i];
 
    vector<Arr> freqs;
    for (size_t i = 0; i < bestLength; ++i)
      freqs.push_back(frequency(pieces[i]));
 
    string key = "";
    for (size_t i = 0; i < bestLength; ++i) 
    {
      sort(freqs[i].begin(), freqs[i].end(), [](pair<char, double> u, pair<char, double> v)->bool { return u.second > v.second; });
 
      size_t m = 0;
      double mCorr = 0.0;
      for (size_t j = 0; j < 26; ++j) 
      {
        double corr = 0.0;
        char c = 'A' + j;
        for (size_t k = 0; k < 26; ++k) 
        {
          int d = (freqs[i][k].first - c + 26) % 26;
          corr += freqs[i][k].second * targets[d];
        }
 
        if (corr > mCorr) 
        {
          m = j;
          mCorr = corr;
        }
      }
 
      key += m + 'A';
    }
 
    string plaintext = "";
    for (size_t i = 0; i < cipher.size(); ++i)
      plaintext += (cipher[i] - key[i % key.length()] + 26) % 26 + 'A';
 
    return make_pair(plaintext, key);
  }
};
 
int main() { 
  
  // Taking the ciphertext from vig2.txt
  string ciphertext = "hdsfgvmkoowafweetcmfthskucaqbilgjofmaqlgspvatvxqbiryscpcfrmvswrvnqlszdmgaoqsakmlupsqforvtwvdfcjzvgsoaoqsacjkbrsevbelvbksarlscdcaarmnvrysywxqgvellcyluwwveoafgclazowafojdlhssfiksepsoywxafowlbfcsocylngqsyzxgjbmlvgrggokgfgmhlmejabsjvgmlnrvqzcrggcrghgeupcyfgtydycjkhqluhgxgzovqswpdvbwsffsenbxapasgazmyuhgsfhmftayjxmwznrsofrsoaopgauaaarmftqsmahvqecevvhasfbxluoxznfhongml";
 
  // Frequencies of the letters in the English alphabet
  array<double, 26> englishFreqs = {
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228,
    0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025,
    0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987,
    0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150,
    0.01974, 0.00074};
 
  Vigenere go(englishFreqs);
  pair<string, string> result = go.decrypt(ciphertext);

  cout << "Key: " << result.second << endl << endl;
  cout << "Plaintext: " << result.first << endl;
}