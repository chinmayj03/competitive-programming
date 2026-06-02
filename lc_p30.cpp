class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int numWords = words.size();
        int wordLength = words[0].length();
        int totalLength = numWords * wordLength;
        int stringLength = s.length();
        unordered_map<string, int> wordFreq;
        for (int i = 0; i < numWords; i++) {
            wordFreq[words[i]]++;
        }

        vector<int> ans;
        int offset = 0;
        while (offset < wordLength) {
            int tail = offset;
            int head = offset - 1;
            unordered_map<string, int> curFreq;
            int curLength = 0;
            while (tail < stringLength) {
                while (head + wordLength < stringLength) {
                    string nextWord = s.substr(head + 1, wordLength);
                    if (wordFreq[nextWord] == 0)
                        break;
                    if (curFreq[nextWord] + 1 > wordFreq[nextWord])
                        break;
                    if (curLength + wordLength > stringLength)
                        break;
                    curFreq[nextWord]++;
                    curLength += wordLength;
                    head += wordLength;
                }

                if (curLength == totalLength)
                    ans.push_back(tail);

                if (tail > head) {
                    tail += wordLength;
                    head = tail - 1;
                } else {
                    string prevWord = s.substr(tail, wordLength);
                    curFreq[prevWord]--;
                    curLength -= wordLength;
                    tail += wordLength;
                }
            }

            offset++;
        }
        return ans;
    }
};