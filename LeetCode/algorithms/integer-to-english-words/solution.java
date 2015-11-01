public class Solution {
    String[] bigNumNames = {"", " Thousand", " Million", " Billion"};
    String[] smallNumNames = {
            "Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine",
            "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"
    };
    String[] tensNames = {"Zero", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Nigety"};


    ArrayList<String> smallNumberToWords(int num) {
        ArrayList<String> ret = new ArrayList<String>();
        if (num >= 100) {
            ret.add(smallNumNames[num/100]);
            ret.add("Hundred");
            num %= 100;
        }

        if (num >= 20) {
            ret.add(tensNames[num/10]);
            num %= 10;
        }

        if (num != 0) {
            ret.add(smallNumNames[num]);
        }

        return ret;
    }

    public String numberToWords(int num) {
        if (num == 0) {
            return smallNumNames[num];
        }

        String ret = "";
        int count = 0;
        while (num > 0) {
            int digit = num % 1000;
            if (digit > 0) {
                String d = String.join(" ", smallNumberToWords(num % 1000));
                d += bigNumNames[count];
                ret = d + (ret.length()>0 ? ' ' + ret : "");
            }
            num /= 1000;
            count++;
        }

        return ret;
    }
}
