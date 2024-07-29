#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define TERM "dk^xj2Dk038*@@JXH!!hhA"

typedef struct
{
    char remote[10];
    char nightShift[10];
    char overtime[10];
    char paidLeave[10];
    char flexible[40];
}Preference;
typedef struct
{
    int hour;
    int min;
}Time;
typedef struct
{
    int seekerID;
    char name[100];
    char industry[100];
    char role[100];
    char skills[10][100];
    char qualification[50];
    char qualField[100];
    char addSkills[10][100];
    int experience;
    int salaryRange[2];
    char location[2][100];
    Time time[2];
    char phoneNumber[20];
    char email[100];
    Preference pref;
}Seeker;
typedef struct
{
    int userID;
    char username[100];
    char password[100];
    char type[10];
    int IDs[10];
}User;
typedef struct
{
    int jobID;
    char orgName[100];
    char industry[100];
    char role[100];
    char skills[10][100];
    char qualification[50];
    char qualField[100];
    char addSkills[10][100];
    int experience;
    int salaryRange[2];
    char location[2][100];
    Time time[2];
    char phoneNumber[20];
    char email[100];
    char salaryDisplay[4];
    Preference pref;
}Recruiter;

Seeker seek[1000];
Recruiter rec[1000];
User user[1000];
int noSeek = 0;
int noRec = 0;
int noUser = 0;

void addSeeker(int loggedID, char loggedType[]);
void seekerMenu(int loggedID, char loggedType[]);
void recruiterMenu(int loggedID, char loggedType[]);
void seekerMenu(int loggedID, char loggedType[]);
void home();

size_t writeData(void* ptr, size_t size, size_t nmemb, FILE* stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}
void readDrive(char* id, char* outputFileName)
{
    CURL* curl;
    FILE* outputFile;
    CURLcode res;

    char driveURL[200] = "https://drive.google.com/uc?export=download&id=";
    strcat(driveURL, id);

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();

    if (curl)
    {
        outputFile = fopen(outputFileName, "w");
        if (!outputFile)
            printf("Failed to open file for writing\n");

        curl_easy_setopt(curl, CURLOPT_URL, driveURL);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, outputFile);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
        fclose(outputFile);
    }
    curl_global_cleanup();
}
void openLink(char* linkName)
{
    char command[200] = "start ";
    strcat(command, linkName);
    system(command);
}
void freeStringArray(char** strArray, int size)
{
    for (int i = 0; i < size; i++)
        free(strArray[i]);
    free(strArray);
}
char** split(char* str1, char d)
{
    char* str = (char*)malloc((strlen(str1) + 2) * sizeof(char));
    strcpy(str, str1);
    int num = 0;
    int charIndex = 0;
    char c = str[charIndex];
    str[strlen(str) + 1] = '\0';
    str[strlen(str)] = d;
    while (c != '\0')
    {
        if (c == d)
            num++;
        charIndex++;
        c = str[charIndex];
    }
    char** arr = (char**)malloc((num + 1) * sizeof(char*));  // Allocate memory for num+1 elements
    charIndex = 0;
    int testIndex = 0;
    int arrIndex = 0;
    char* test = (char*)malloc((strlen(str) + 1) * sizeof(char));  // Allocate memory for test
    c = str[charIndex];
    while (c != '\0')
    {
        if (c != d)
        {
            test[testIndex] = c;
            testIndex++;
        }
        else
        {
            test[testIndex] = '\0';  // Append null terminator
            arr[arrIndex] = (char*)malloc((testIndex + 1) * sizeof(char));
            strcpy(arr[arrIndex], test);
            testIndex = 0;
            arrIndex++;
        }
        charIndex++;
        c = str[charIndex];
    }
    arr[arrIndex] = NULL;  // Add NULL terminator to the end of arr
    free(test);  // Free the memory allocated for test
    free(str);
    return arr;
}
int readUsers(User user[]) {
    FILE* file = fopen("users.csv", "r");
    if (file == NULL) {
        printf("Error opening file %s\n", "users.csv");
        return 0;
    }

    char line[200];
    int count = 0;

    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ",");
        if (token != NULL) {
            user[count].userID = atoi(token);
            token = strtok(NULL, ",\n");
            strcpy(user[count].username, token);
            token = strtok(NULL, ",\n");
            strcpy(user[count].password, token);
            token = strtok(NULL, ",\n");
            strcpy(user[count].type, token);
            count++;
        }
    }

    fclose(file);
    return count;
}
int countStrings(char arr[][100]) {
    int count = 0;
    int i = 0;

    while (strcmp(arr[i], TERM) != 0) {
        count++;
        i++;
    }
    return count;
}

float power(float a, int b) {
    if (b == 1)
        return a;
    else
        return a * power(a, b - 1);
}
int hourToMin(int hours, int mins) {
    int minutes = hours * 60 + mins;
    return minutes;
}
void selectionSort(float arr[], int n)
{
    int i, j, maxIndex;
    float temp;

    for (i = 0; i < n - 1; i++)
    {
        maxIndex = i;
        for (j = i + 1; j < n; j++)
        {
            if (arr[j] > arr[maxIndex])
            {
                maxIndex = j;
            }
        }
        temp = arr[maxIndex];
        arr[maxIndex] = arr[i];
        arr[i] = temp;
    }
}
void collectData()
{
    FILE* fps, * fpr, * fpu;
    int i = 0, k = 0, len = 0;
    noSeek = 0;
    noUser = 0;
    noRec = 0;
    fps = fopen("Seekers.csv", "r");
    fpr = fopen("Recruiters.csv", "r");
    fpu = fopen("Users.csv", "r");
    char skills[1000];
    char addskills[1000];
    char starttime[20];
    char endtime[20];
    char ids[200];
    char** skillsArr;
    char** addSkillsArr;
    char** idArr;
    char c = ' ';
    int hour, min;
    char ampm[3];
    char str[10000];
    int a;
    if (fpr == NULL)
        printf("Failed to open the file.\n");
    if (fps == NULL)
        printf("Failed to open the file.\n");
    if (fpu == NULL)
        printf("Failed to open the file.\n");

    while (fgets(str, 10000, fpu) != NULL)
    {
        int read;
        strcpy(ids, "-1");
        read = sscanf(str, "%d,%[^,],%[^,],%[^,],%s\n", &user[i].userID, user[i].username, user[i].password, user[i].type, ids);
        idArr = split(ids, ',');
        while (idArr[k] != NULL)
        {
            user[i].IDs[k] = atoi(idArr[k]);
            k++;
        }
        k = 0;
        i++;
        noUser++;
    }
    i = 0;
    k = 0;
    while (fgets(str, 10000, fps) != NULL)
    {
        sscanf(str, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%d-%d,%[^;];%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]\n", &seek[i].seekerID, seek[i].name, seek[i].industry, seek[i].role, skills, seek[i].qualification, seek[i].qualField, addskills, &seek[i].experience, &seek[i].salaryRange[0], &seek[i].salaryRange[1], seek[i].location[0], seek[i].location[1], starttime, endtime, seek[i].phoneNumber, seek[i].email, seek[i].pref.remote, seek[i].pref.nightShift, seek[i].pref.overtime, seek[i].pref.paidLeave, seek[i].pref.flexible);
        sscanf(starttime, "%d:%d:00 %s", &hour, &min, ampm);
        if (strcmp(ampm, "PM") == 0)
            hour += 12;
        seek[i].time[0].hour = hour;
        seek[i].time[0].min = min;
        sscanf(endtime, "%d:%d:00 %s", &hour, &min, ampm);
        if (strcmp(ampm, "PM") == 0)
            hour += 12;
        seek[i].time[1].hour = hour;
        seek[i].time[1].min = min;
        skillsArr = split(skills, ';');
        while (skillsArr[k] != NULL)
        {
            strcpy(seek[i].skills[k], skillsArr[k]);
            k++;
        }
        strcpy(seek[i].skills[k], TERM);
        k = 0;
        freeStringArray(skillsArr, sizeof(skillsArr));
        addSkillsArr = split(addskills, ';');
        while (addSkillsArr[k] != NULL)
        {
            strcpy(seek[i].addSkills[k], addSkillsArr[k]);
            k++;
        }
        strcpy(seek[i].addSkills[k], TERM);
        k = 0;
        freeStringArray(addSkillsArr, sizeof(addSkillsArr));
        i++;
        noSeek++;
    }
    i = 0;
    k = 0;
    while (fgets(str, 10000, fpr) != NULL)
    {
        sscanf(str, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%d-%d,%[^;];%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]\n", &rec[i].jobID, rec[i].orgName, rec[i].industry, rec[i].role, skills, rec[i].qualification, rec[i].qualField, addskills, &rec[i].experience, &rec[i].salaryRange[0], &rec[i].salaryRange[1], rec[i].location[0], rec[i].location[1], starttime, endtime, rec[i].salaryDisplay, rec[i].phoneNumber, rec[i].email, rec[i].pref.remote, rec[i].pref.nightShift, rec[i].pref.overtime, rec[i].pref.paidLeave, rec[i].pref.flexible);
        sscanf(starttime, "%d:%d:00 %s", &hour, &min, ampm);
        if (strcmp(ampm, "PM") == 0)
            hour += 12;
        rec[i].time[0].hour = hour;
        rec[i].time[0].min = min;
        sscanf(endtime, "%d:%d:00 %s", &hour, &min, ampm);
        if (strcmp(ampm, "PM") == 0)
            hour += 12;
        rec[i].time[1].hour = hour;
        rec[i].time[1].min = min;
        skillsArr = split(skills, ';');
        while (skillsArr[k] != NULL)
        {
            strcpy(rec[i].skills[k], skillsArr[k]);
            k++;
        }
        strcpy(rec[i].skills[k], TERM);
        k = 0;
        addSkillsArr = split(addskills, ';');
        while (addSkillsArr[k] != NULL)
        {
            strcpy(rec[i].addSkills[k], addSkillsArr[k]);
            k++;
        }
        strcpy(rec[i].addSkills[k], TERM);
        k = 0;
        i++;
        noRec++;
    }
    fclose(fpr);
    fclose(fps);
    fclose(fpu);
}
float computePercentage(Seeker seek, Recruiter rec) {
    int weight = 0;
    float score = 0;
    float net_value = 0;
    int total_weight = 0;

    // Flexibility
    char flex[][50] = { "Flexible only with pay", "Flexible only with working conditions", "Flexible with all", "Not flexible" };
    int flex_reqd = 0;
    int flex_act = 0;
    for (int i = 0; i < 4; i++) {
        if (strcmp(flex[i], rec.pref.remote) == 0) {
            flex_reqd = i;
        }
        if (strcmp(flex[i], seek.pref.remote) == 0) {
            flex_act = i;
        }
    }

    // Industry
    if (strcmp(seek.industry, rec.industry) == 0) {
        weight = 100;
        score = 10;
    }
    else {
        weight = 0;
        score = 0;
    }
    net_value += (weight * score);
    total_weight += weight;

    // Role
    if (strcmp(seek.role, rec.role) == 0) {
        weight = 200;
        score = 10;
    }
    else {
        weight = 10;
        score = 0;
    }
    net_value += (weight * score);
    total_weight += weight;

    // Required Skills
    int num_match = 0;
    int total_skills = countStrings(rec.skills);

    for (int i = 0; strcmp(seek.skills[i], TERM) != 0; i++) {
        for (int j = 0; strcmp(rec.skills[j], TERM) != 0; j++) {
            if (strcmp(seek.skills[i], rec.skills[j]) == 0)
                num_match += 1;
        }
    }

    if (num_match > 0) {
        weight = 50;
        score = 10 * (float)num_match / total_skills;
    }
    else {
        weight = 10;
        score = 0;
    }
    net_value += (weight * score);
    total_weight += weight;


    // Qualification
    char qual_opts[][30] = { "No education / 10th Standard", "12th Standard", "Diploma", "Undergraduate Degree", "Postgraduate Degree", "PHD and above" };
    int i, len = 6;
    int loc_reqd = 0, loc_act = 0;
    for (i = 0; i < 6; i++) {
        if (strcmp(qual_opts[i], rec.qualification) == 0) {
            loc_reqd = i;
            break;
        }
    }
    for (i = 0; i < 6; i++) {
        if (strcmp(qual_opts[i], seek.qualification) == 0) {
            loc_act = i;
            break;
        }
    }
    if (loc_reqd == loc_act) {
        weight = 60;
        score = 10;
    }
    else if (loc_reqd < loc_act) {
        weight = 60;
        score = 6;
    }
    else if (loc_reqd > loc_act) {
        weight = 300;
        score = 0;
    }
    net_value += (weight * score);
    total_weight += weight;


    // Field of work
    char grouped_fields[][11][100] = { {"Agriculture;Agriculture Operations;and Related Sciences","Natural Resources and Conservation","Parks;Recreation;Leisure;and Fitness Studies"},{"Social Sciences","Theology and Religious Vocations","Foreign Languages;Literatures;and Linguistics","Area;Ethnic;Cultural;Gender;and Group Studies","English Language and Literature/letters","Philosophy and Religious Studies","History","Education","Visual and Performing Arts","Liberal Arts and Sciences Studies and Humanities","Library Science"},{"Transportation and Materials Moving","Architecture and Related Services","Construction Trades"},{"Aviation",},{"Biological and Biomedical Sciences","Health Professions and Related Programs"},{"Business;Management;Marketing;and Related Support Services","Communication;Journalism;and Related Programs","Communications Technologies/technicians and Support Services","Computer and Information Sciences and Support Services","Mathematics and Statistics","Precision Production"},{"Engineering Technologies and Engineering-Related Fields","Engineering","Mechanic and Repair Technologies/technicians","Science Technologies/technicians","Physical Sciences"},{"Family and Consumer Sciences/human Sciences","Psychology","Personal and Culinary Services","Multi/interdisciplinary Studies"},{"Homeland Security;Law Enforcement;Firefighting","Human Services","Military Technologies and Applied Sciences"},{"Legal Professions and Studies"},{"No Degree"} };
    weight = 300;

    char reqd_field[100];
    strcpy(reqd_field, rec.qualField);
    char act_field[100];
    strcpy(act_field, seek.qualField);
    if (strcmp(reqd_field, act_field) == 0) {
        score = 10;
    }
    else {
        int groupnum_reqd = 0;
        int groupnum_act = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 11; j++) {
                if (strcmp(grouped_fields[i][j], reqd_field) == 0) {
                    groupnum_reqd = i;
                }
                if (strcmp(grouped_fields[i][j], act_field) == 0) {
                    groupnum_act = i;
                }
            }
        }
        if (groupnum_reqd == groupnum_act) {
            score = 5;
        }
        else {
            score = 0;
        }
    }
    net_value += (weight * score);
    total_weight += weight;


    // Additional Skills
    int num_match_add = 0;
    int total_add_skills = countStrings(rec.addSkills);

    for (int i = 0; strcmp(seek.addSkills[i], TERM) != 0; i++) {
        for (int j = 0; strcmp(rec.addSkills[j], TERM) != 0; j++) {
            if (strcmp(seek.addSkills[i], rec.addSkills[j]) == 0)
                num_match_add += 1;
        }
    }

    if (num_match > 0) {
        weight = 15;
        score = 10 * (float)num_match_add / total_add_skills;
    }
    else {
        weight = 3;
        score = 0;
    }
    net_value += (weight * score);
    total_weight += weight;

    // Years of Experience
    int reqd_years = rec.experience;
    int act_years = seek.experience;
    int diff = 0;

    weight = 30;
    if (act_years < reqd_years) {
        diff = reqd_years - act_years;
        score = 10 - power((float)5 / 4, diff); // 25% compound decrease
    }
    else if (act_years > reqd_years) {
        diff = act_years - reqd_years;
        score = 10 - power((float)11 / 10, diff); // 10% compund deccrease
    }
    else {
        score = 10;
    }
    net_value += (weight * score);
    total_weight += weight;


    // Salary Range
    weight = 15;
    if (flex_reqd == 1 || flex_act == 1 || flex_reqd == 3 || flex_reqd == 3)
        weight = 150;
    int reqd_diff = rec.salaryRange[1] - rec.salaryRange[0];
    int act_diff = seek.salaryRange[1] - seek.salaryRange[0];
    int smaller = 0;
    if (reqd_diff < act_diff)
        smaller = reqd_diff;
    else
        smaller = act_diff;

    int count = 0;
    if (rec.salaryRange[0] <= seek.salaryRange[1] && seek.salaryRange[0] <= rec.salaryRange[1]) {
        int start = (rec.salaryRange[0] > seek.salaryRange[0]) ? rec.salaryRange[0] : seek.salaryRange[0];
        int end = (rec.salaryRange[1] < seek.salaryRange[1]) ? rec.salaryRange[1] : seek.salaryRange[1];
        count = end - start;
    }
    score = (float)count / smaller;

    net_value += (weight * score);
    total_weight += weight;

    // Location 
    weight = 30;
    if (flex_reqd == 0 || flex_act == 0 || flex_reqd == 3 || flex_reqd == 3)
        weight = 150;
    if (strcmp(rec.location[0], seek.location[0]) == 0 && strcmp(rec.location[1], seek.location[1]) == 0) {
        score = 10;
    }
    else if (strcmp(rec.location[0], seek.location[0]) != 0 && strcmp(rec.location[1], seek.location[1]) == 0) {
        score = 4;
    }
    else {
        score = 0;
    }
    net_value += (weight * score);
    total_weight += weight;

    // Timings
    weight = 25;
    if (flex_reqd == 0 || flex_act == 0 || flex_reqd == 3 || flex_reqd == 3)
        weight = 50;
    int reqd_start, reqd_end, act_start, act_end;
    reqd_start = hourToMin(rec.time[0].hour, rec.time[0].min);
    reqd_end = hourToMin(rec.time[1].hour, rec.time[1].min);
    act_start = hourToMin(seek.time[0].hour, seek.time[0].min);
    act_end = hourToMin(seek.time[1].hour, seek.time[1].min);
    reqd_diff = reqd_end - reqd_start;
    act_diff = act_end - act_start;
    int larger = 0;
    if (reqd_diff > act_diff)
        larger = reqd_diff;
    else
        larger = act_diff;

    int count_t = 0;
    int start, end;
    if (reqd_start <= act_end && act_start <= reqd_end) {
        start = (reqd_start > act_start) ? reqd_start : act_start;
        end = (reqd_end < act_end) ? reqd_end : act_end;
        count_t = end - start;
    }
    score = (float)count_t / larger;
    net_value += (weight * score);
    total_weight += weight;

    // Preferences
    char preferences[][10] = { "Always", "Often", "Rarely", "Never" };

    // Remote work
    weight = 8;
    if (flex_reqd == 0 || flex_act == 0 || flex_reqd == 3 || flex_reqd == 3)
        weight = 30;
    int rem_reqd = 0;
    int rem_act = 0;
    for (int i = 0; i < 4; i++) {
        if (strcmp(preferences[i], rec.pref.remote) == 0) {
            rem_reqd = i;
        }
        if (strcmp(preferences[i], seek.pref.remote) == 0) {
            rem_act = i;
        }
    }
    diff = rem_reqd - rem_act;
    if (diff == 0) {
        score = 10;
    }
    else if (diff == 1 || diff == -1) {
        score = 6;
    }
    else if (diff == 2 || diff == -2) {
        score = 3;
    }
    else if (diff == 3 || diff == -3) {
        weight = 30;
        score = 0;
    }
    net_value += (weight * score);
    total_weight += weight;
    // Night Shift 
    weight = 8;
    if (flex_reqd == 0 || flex_act == 0 || flex_reqd == 3 || flex_reqd == 3)
        weight = 30;
    int shift_reqd = 0;
    int shift_act = 0;
    for (int i = 0; i < 4; i++) {
        if (strcmp(preferences[i], rec.pref.nightShift) == 0) {
            shift_reqd = i;
        }
        if (strcmp(preferences[i], seek.pref.nightShift) == 0) {
            shift_act = i;
        }
    }
    diff = shift_reqd - shift_act;
    if (diff == 0) {
        score = 10;
    }
    else if (diff == 1 || diff == -1) {
        score = 6;
    }
    else if (diff == 2 || diff == -2) {
        score = 3;
    }
    else if (diff == 3 || diff == -3) {
        weight = 30;
        score = 0;
    }
    net_value += (weight * score);
    total_weight += weight;
    // Overtime
    weight = 8;
    if (flex_reqd == 0 || flex_act == 0 || flex_reqd == 3 || flex_reqd == 3)
        weight = 16;
    int overtime_reqd = 0;
    int overtime_act = 0;
    for (int i = 0; i < 4; i++) {
        if (strcmp(preferences[i], rec.pref.overtime) == 0) {
            overtime_reqd = i;
        }
        if (strcmp(preferences[i], seek.pref.overtime) == 0) {
            overtime_act = i;
        }
    }
    diff = overtime_reqd - overtime_act;
    if (diff < 0)
        diff = -diff;
    if (diff == 0) {
        score = 10;
    }
    else if (diff == 1 || diff == -1) {
        score = 6;
    }
    else if (diff == 2 || diff == -2) {
        score = 3;
    }
    else if (diff == 3 || diff == -3) {
        weight = 30;
        score = 0;
    }
    net_value += (weight * score);
    total_weight += weight;
    // Paid Leave
    if (flex_reqd == 0 || flex_act == 0 || flex_reqd == 3 || flex_reqd == 3)
        weight = 16;
    char leavePreferences[][10] = { "10-15", "15-20", "20-25", "25+" };
    weight = 8;
    int pl_reqd = 0;
    int pl_act = 0;
    for (int i = 0; i < 4; i++) {
        if (strcmp(leavePreferences[i], rec.pref.paidLeave) == 0) {
            pl_reqd = i;
        }
        if (strcmp(leavePreferences[i], seek.pref.paidLeave) == 0) {
            pl_act = i;
        }
    }
    diff = pl_reqd - pl_act;
    if (diff == 0) {
        score = 10;
    }
    else if (diff == 1 || diff == -1) {
        score = 6;
    }
    else if (diff == 2 || diff == -2) {
        score = 3;
    }
    else if (diff == 3 || diff == -3) {
        weight = 30;
        score = 0;
    }
    net_value += (weight * score);
    total_weight += weight;
    // Percentage computation
    float percentage = net_value / total_weight * 10;
    return percentage;
}

void setID(int loggedID, char loggedType[])
{
    FILE *fp1, *fp2;
    fp1 = fopen("Users.csv", "r");
    fp2 = fopen("Temp.txt", "w");

    int index = 0;
    char str[10000], strn[10000];
    int cnt = 0;

    for (int i = 0; i < noUser; i++)
    {
        if (user[i].userID == loggedID)
            index = i;
    }
    while (fgets(str, 10000, fp1) != NULL)
    {
        if (index == cnt)
        {
            str[strlen(str) - 1] = '\0';
            if (strcmp(loggedType, "Recruiter") == 0)
                fprintf(fp2, "%s,%d\n", str, rec[noRec - 1].jobID);
            else
                fprintf(fp2, "%s,%d\n", str, seek[noSeek - 1].seekerID);
        }
        else
            fprintf(fp2, "%s", str);
        cnt++;
    }
    fclose(fp1);
    fclose(fp2);
    
    FILE* fp3, *fp4;
    fp3 = fopen("Users.csv", "w");
    fp4 = fopen("Temp.txt", "r");
    while (fgets(str, 10000, fp4) != NULL)
    {
        fprintf(fp3, "%s", str);
    }
    fclose(fp3);
    fclose(fp4);
}
void searchApplicants(int loggedID, char loggedType[]) {
    float percent_matches[noSeek];
    float pc_sorted[noSeek];
    int recruiterID;
    int idArr[10];
    for (int i = 0; i < 10; i++)
        idArr[i] = -1;
    for (int i = 0; i < noUser; i++) {
        if (user[i].userID == loggedID) {
            for (int j = 0; j < 10; j++)
            {
                idArr[j] = user[i].IDs[j];
                if (idArr[j] == 0)
                    idArr[j] = -1;
            }
        }
    }
    if (idArr[0] == -1)
    {
        printf("\nPlease add job before searching for applicants\n");
        recruiterMenu(loggedID, loggedType);
    }
    printf("%-*s%-*s%-*s\n", 10, "Job ID", 30, "Organisation Name", 30, "Job Role");
    for (int i = 0; idArr[i] != -1; i++) {
        for (int j = 0; j < noRec; j++)
        {
            if (rec[j].jobID == idArr[i])
            {
                printf("%-*d%-*s%-*s%\n", 10, rec[j].jobID, 30, rec[j].orgName, 30, rec[j].role);
            }
        }
    }
    printf("\nChoose JobID:\n");
    scanf("%d", &recruiterID);

    for (int i = 0; i < noRec; i++)
    {
        if (rec[i].jobID == recruiterID)
        {
            for (int j = 0; j < noSeek; j++)
            {
                percent_matches[j] = computePercentage(seek[j], rec[i]);
                pc_sorted[j] = percent_matches[j];
            }
        }
    }
    int index_percent = 0;
    selectionSort(pc_sorted, noSeek);
    printf("Top five seeker matches:\n\n");
    printf("%-*s%-*s%-*s%-*s\n", 20, "Seeker ID", 30, "Name", 40, "Job Role", 0, "Percentage");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < noSeek; j++) {
            if (pc_sorted[i] == percent_matches[j]) {
                printf("%-*d%-*s%-*s%-*.2f\n", 20, seek[j].seekerID, 30, seek[j].name, 40, seek[j].role, 0, percent_matches[j]);
            }
        }
    }
    int seeker_to_display;
    printf("\nEnter the seekerID to be displayed:\n");
    scanf("%d", &seeker_to_display);

    for (int i = 0; i < noSeek; i++) {
        if (seek[i].seekerID == seeker_to_display) {
            printf("\nThe Seeker Details details are:\n");
            printf("Job ID: %d\n", seek[i].seekerID);
            printf("Applicant Name: %s\n", seek[i].name);
            printf("Industry: %s\n", seek[i].industry);
            printf("Role: %s\n", seek[i].role);
            printf("Qualification: %s\n", seek[i].qualification);
            printf("Qualification Field: %s\n", seek[i].qualField);
            printf("Experience: %d years\n", seek[i].experience);
            printf("Salary Range: %d - %d\n", seek[i].salaryRange[0], seek[i].salaryRange[1]);
            printf("Location: %s, %s\n", seek[i].location[0], seek[i].location[1]);
            printf("Timings: %02d:%02d - %02d:%02d\n", seek[i].time[0].hour, seek[i].time[0].min, seek[i].time[1].hour, seek[i].time[1].min);
            printf("Phone Number: %s\n", seek[i].phoneNumber);
            printf("Email: %s\n", seek[i].email);

            // Display preferences
            printf("Preferences:\n");
            printf("Remote: %s\n", seek[i].pref.remote);
            printf("Night Shift: %s\n", seek[i].pref.nightShift);
            printf("Overtime: %s\n", seek[i].pref.overtime);
            printf("Paid Leave: %s\n", seek[i].pref.paidLeave);
            printf("Flexible: %s\n", seek[i].pref.flexible);

        }
    }
    recruiterMenu(loggedID, loggedType);
}
void addJob(int loggedID, char loggedType[])
{
    char chk;
    openLink("https://docs.google.com/forms/d/e/1FAIpQLSfSgNaHSqi2yJalK5AxIklYIBZ2io2T831Yc5uB5GUuil2TZg/viewform?usp=sf_link");
    printf("Please enter 'X' ONLY when you have filled and submitted the form. DO NOT close this application until you have submitted the form\n");
    do
    {
        scanf("%c", &chk);
    } while (chk != 'X');
    readDrive("1ImQ9m82OmLBBRGcFVQhTh-BRS7YJ-qkF", "Recruiters.csv");
    Sleep(5);
    collectData();
    setID(loggedID, loggedType);
    collectData();
    recruiterMenu(loggedID, loggedType);
}
void recruiterMenu(int loggedID, char loggedType[])
{
    int choice;
    printf("\nWelcome to the Recruiter Menu! Choose one of the following options to perform\n");
    printf("Enter 1 : Add Job\n");
    printf("Enter 2 : Search for Seekers\n");
    printf("Enter 3 : Exit Application\n");
    printf("\nEnter choice : ");
    scanf("%d", &choice);

    do
    {
        switch (choice)
        {
        case 1:
            addJob(loggedID, loggedType);
            break;
        case 2:
            searchApplicants(loggedID, loggedType);
            break;
        case 3:
            exit(0);
            break;
        default:
            printf("Please enter a valid option\n");
            printf("\nEnter choice : ");
            scanf("%d", &choice);
            break;
        }
    } while (choice < 1 && choice > 3);

}
void searchJobs(int loggedID, char loggedType[]) {
    float percent_matches[noRec];
    float pc_sorted[noRec];
    int seekerID;
    for (int i = 0; i < noUser; i++) {
        if (user[i].userID == loggedID) {
            seekerID = user[i].IDs[0];
        }
    }
    if (seekerID == -1)
    {
        printf("\nPlease add seeker details before searching for Jobs\n");
        seekerMenu(loggedID, loggedType);
    }
    for (int i = 0; i < noSeek; i++)
    {
        if (seek[i].seekerID == seekerID)
        {
            for (int j = 0; j < noRec; j++)
            {
                percent_matches[j] = computePercentage(seek[i], rec[j]);
                pc_sorted[j] = percent_matches[j];
            }
        }
    }
    int index_percent = 0;
    selectionSort(pc_sorted, noRec);
    printf("Top five job matches:\n\n");
    printf("%-*s%-*s%-*s%-*s\n", 10, "Job ID", 30, "Organisation Name", 30, "Job Role", 0, "Percentage");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < noRec; j++) {
            if (pc_sorted[i] == percent_matches[j]) {
                printf("%-*d%-*s%-*s%-*.2f\n", 10, rec[j].jobID, 30, rec[j].orgName, 40, rec[j].role, 0, percent_matches[j]);
            }
        }
    }
    int job_to_display;
    printf("\nEnter the jobID to display more details: ");
    scanf("%d", &job_to_display);

    for (int i = 0; i < noRec; i++) {
        if (rec[i].jobID == job_to_display) {
            printf("\nThe Job Details details are:\n");
            printf("Job ID: %d\n", rec[i].jobID);
            printf("Organization Name: %s\n", rec[i].orgName);
            printf("Industry: %s\n", rec[i].industry);
            printf("Role: %s\n", rec[i].role);
            printf("Qualification: %s\n", rec[i].qualification);
            printf("Qualification Field: %s\n", rec[i].qualField);
            printf("Experience: %d years\n", rec[i].experience);
            if (strcmp(rec[i].salaryDisplay, "yes") == 0)
                printf("Salary Range: %d - %d\n", rec[i].salaryRange[0], rec[i].salaryRange[1]);
            printf("Location: %s, %s\n", rec[i].location[0], rec[i].location[1]);
            printf("Timings: %02d:%02d - %02d:%02d\n", rec[i].time[0].hour, rec[i].time[0].min, rec[i].time[1].hour, rec[i].time[1].min);
            printf("Phone Number: %s\n", rec[i].phoneNumber);
            printf("Email: %s\n", rec[i].email);

            // Display preferences
            printf("Preferences:\n");
            printf("Remote: %s\n", rec[i].pref.remote);
            printf("Night Shift: %s\n", rec[i].pref.nightShift);
            printf("Overtime: %s\n", rec[i].pref.overtime);
            printf("Paid Leave: %s\n", rec[i].pref.paidLeave);
            printf("Flexible: %s\n", rec[i].pref.flexible);

        }
    }
    seekerMenu(loggedID, loggedType);
}
void addSeeker(int loggedID, char loggedType[])
{
    int seekerID;
    for (int i = 0; i < noUser; i++) {
        if (user[i].userID == loggedID) {
            seekerID = user[i].IDs[0];
        }
    }
    if (seekerID != -1)
    {
        printf("\nYou may not fill the form twice\n");
        seekerMenu(loggedID, loggedType);
    }
    char chk;
    openLink("https://docs.google.com/forms/d/e/1FAIpQLScwUhmRfKA-9Fl-gSnT_c9zR0oAFx32_IQukQfsx717f9nDtw/viewform?usp=sf_link");
    printf("Please enter 'X' ONLY when you have filled and submitted the form. DO NOT close this application until you have submitted the form\n");
    do
    {
        scanf("%c", &chk);
    } while (chk != 'X');
    readDrive("1ez0p7EBMXRmtBMNEqbNBUX0E4dlnGFV2", "Seekers.csv");
    Sleep(5);
    collectData();
    setID(loggedID, loggedType);
    collectData();
    seekerMenu(loggedID, loggedType);
}
void seekerMenu(int loggedID, char loggedType[])
{
    int choice;
    printf("\nWelcome to the Seeker Menu! Choose one of the following options to perform\n");
    printf("Enter 1 : Add seeker details\n");
    printf("Enter 2 : Search for Jobs\n");
    printf("Enter 3 : Exit Application\n");
    printf("\nEnter choice : ");
    scanf("%d", &choice);

    do
    {
        switch (choice)
        {
        case 1:
            addSeeker(loggedID, loggedType);
            break;
        case 2:
            searchJobs(loggedID, loggedType);
            break;
        case 3:
            exit(0);
            break;
        default:
            printf("Please enter a valid option\n");
            printf("\nEnter choice : ");
            scanf("%d", &choice);
            break;
        }
    } while (choice < 1 && choice > 3);
}
void signUp()
{
    char c;
    char username[90];
    char password[90], password2[90];
    char type[10];
    char dummy[100];
    char str[500];
    char chk[100];
    int chkID;
    int userID;
    int choice = 1;
    FILE* fpu;
    fpu = fopen("Users.csv", "r+");
    printf("\n1.Please do not use commas or spaces in the username or password\n2.Please maintain a character limit of 90\n");
    printf("Enter Username: ");
    scanf("%s", username);
    userID = (float)rand() / RAND_MAX * 900000 + 100000;
    while (fgets(str, 500, fpu))
    {
        sscanf(str, "%d,%[^,],%s\n", &chkID, chk, dummy);
        if (strcmp(chk, username) == 0)
        {
            printf("Username already exists\n");
            fclose(fpu);
            signUp();
        }
        else if (strcmp(username, "Sign-Up") == 0)
        {
            printf("Invalid Username\n");
            fclose(fpu);
            signUp();
        }
        else if (userID == chkID)
        {
            userID = (float)rand() / RAND_MAX * 900000 + 100000;
            rewind(fpu);
        }
    }
    printf("Enter Password: ");
    scanf("%s", password);
    printf("Re-enter Password: ");
    scanf("%s", password2);
    if (strcmp(password, password2) != 0)
    {
        printf("Passowords do not match");
        fclose(fpu);
        signUp();
    }
    do
    {
        if (choice != 1 && choice != 2)
            printf("Please enter a valid choice\n");
        printf("Enter 1 for recruiter account. Enter 2 for a seeker account\n");
        scanf("%d", &choice);
    } while (choice != 1 && choice != 2);
    if (choice == 1)
        strcpy(type, "Recruiter\0");
    else if (choice == 2)
        strcpy(type, "Seeker\0");

    fprintf(fpu, "%d,%s,%s,%s\n", userID, username, password, type);
    fclose(fpu);
    c = getc(stdin);
    home();
}
User* login(int numUsers) {
    char username[50];
    char password[50];
    printf("\nWelcome to the login page. Type 'Sign-Up' as username in order to Sign-Up for a new account. Otherwise, enter username.\n");
    printf("Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';
    if (strcmp(username, "Sign-Up") == 0)
    {
        signUp();
        return NULL;
    }
    printf("Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(user[i].username, username) == 0 && strcmp(user[i].password, password) == 0) {
            User* loggedInUser = malloc(sizeof(User));
            if (loggedInUser == NULL) {
                printf("Error allocating memory.\n");
                return NULL;
            }
            *loggedInUser = user[i];
            return loggedInUser;
        }
    }

    printf("Invalid username or password.\n");
    return NULL;
}

void printUserInfo(User* user) {
    printf("\nLogged in successfully.\n");
    printf("User ID: %d\n", user->userID);
    printf("Username: %s\n", user->username);
    printf("Account Type: %s\n", user->type);
}

void home() {
    int numUsers = readUsers(user);
    User* loggedInUser = login(numUsers);
    int loggedID;
    char loggedType[10];
    if (loggedInUser != NULL) {
        loggedID = loggedInUser->userID;
        strcpy(loggedType, loggedInUser->type);
        printUserInfo(loggedInUser);
        free(loggedInUser);
    }
    else
        home();
    collectData();
    if (strcmp(loggedType, "Recruiter") == 0)
        recruiterMenu(loggedID, loggedType);
    else
        seekerMenu(loggedID, loggedType);
}
int main()
{
    home();
    return 0;
}