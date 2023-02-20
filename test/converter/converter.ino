//for testing on arduino uno
int ArrToInt(uint8_t* arr)
{
    long output = 0;
    for(int i = 0; i < 8; i++)
    {
        output <<= 8;
        output += arr[i];
    }
    return output;
}

void IntToArr(long num, uint8_t* arr)
{
    for(int i = 0; i < 8; i++)
    {
        arr[8 - i - 1] = (uint8_t) (num & 0xFF);
        num >>= 8;
    }
}
void setup(void) {
    Serial.begin(9600);
    long long num = -14576;
    uint8_t arr[8];
    /* //most of the testing was done in visual studio for c++ good ol CS33 style
    for (unsigned long long i = 0; i < 18446744073709551615; i++)
    {
        num = i;
        IntToArr(num, arr);
        long long output = ArrToInt(arr);
        assert(num == output);
        cout << i << endl;
    }
    */
    IntToArr(num, arr);
    Serial.println(ArrToInt(arr));
}

void loop() {

}