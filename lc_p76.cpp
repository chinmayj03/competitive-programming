class Solution {
public:
    string minWindow(string s, string t) {
        int lengthS = s.length();
        int lengthT = t.length();

        if (lengthS < lengthT) return "";

        vector<int> charT(256, 0);
        vector<int> charCur(256, 0);

        for (char ch : t) {
            charT[static_cast<unsigned char>(ch)]++;
        }

        int tail = 0, head = -1;
        int minLength = lengthS + 1;
        int ansStart = -1;

        int matched = 0;

        while (tail < lengthS) {

            while (head + 1 < lengthS && matched < lengthT) {
                unsigned char nextChar = static_cast<unsigned char>(s[head + 1]);

                if (charT[nextChar] != 0 &&
                    charCur[nextChar] + 1 <= charT[nextChar]) {
                    matched++;
                }

                charCur[nextChar]++;
                head++;
            }

            if (matched == lengthT) {
                int curLength = head - tail + 1;

                if (curLength < minLength) {
                    minLength = curLength;
                    ansStart = tail;
                }
            }

            if (tail > head) {
                tail++;
                head = tail - 1;
            } else {
                unsigned char tailChar = static_cast<unsigned char>(s[tail]);

                if (charT[tailChar] != 0 &&
                    charCur[tailChar] <= charT[tailChar]) {
                    matched--;
                }

                charCur[tailChar]--;
                tail++;
            }
        }

        if (ansStart == -1) return "";

        return s.substr(ansStart, minLength);
    }
};