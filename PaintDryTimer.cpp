#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>

#include "TimeCode.h"

using namespace std;

struct Batch
{
    string id;
    TimeCode* remaining;  // Heap-allocated TimeCode that stores the current amount of time remaining.
    time_t start; // Time when the batch was started.
    time_t end; // Time when the batch will finish.
};

double SurfaceArea(double radius)
{
    return 4.0 * acos(-1.0) * radius * radius;
}

void DeleteFinishedBatches(vector<Batch>& batches)
{
    for (size_t i = 0; i < batches.size();)
    {
        time_t now = time(0);

        // If the current time has reached the ending time,
        // the batch is finished.
        if (now >= batches[i].end)
        {
            cout << batches[i].id << " DONE!" << endl;

            delete batches[i].remaining; // Delete the heap-allocated TimeCode.

            batches.erase(batches.begin() + i); // Remove the batch from the vector.
        }
        else
        {
            ++i;
        }
    }
}

void UpdateRemaining(Batch& batch)
{
    time_t now = time(0);

    time_t elapsed = now - batch.start;

    time_t totalSeconds = batch.end - batch.start; // Calculate the total amount of time the batch was supposed to take.

    time_t remainingSeconds = totalSeconds - elapsed;
    
    if (remainingSeconds < 0) remainingSeconds = 0; // Make sure the value never becomes negative.
    
    // Update the same heap-allocated TimeCode.
    *(batch.remaining) = TimeCode(0, 0, static_cast<unsigned long long int>(remainingSeconds));
}

void AddBatch(vector<Batch>& batches)
{
    double radius;

    cout << "radius: ";
    cin >> radius;

    if (!cin || radius < 0)
    {
        cin.clear();
        cin.ignore(10000, '\n');

        cout << "Invalid radius." << endl;

        return;
    }

    // A batch takes n seconds, where n is the surface area of one sphere.
    unsigned long long int seconds = static_cast<unsigned long long int>(SurfaceArea(radius));

    Batch batch;

    batch.id = "Batch-" + to_string(rand());

    // Allocate one TimeCode on the heap for this batch.
    batch.remaining = new TimeCode(0, 0, seconds);

    // Record when the batch starts.
    batch.start = time(0);

    // Record when the batch should finish.
    batch.end = batch.start + static_cast<time_t>(seconds);

    batches.push_back(batch);

    cout << batch.id << " time remaining: " << batch.remaining->ToString() << endl;
}

void ViewBatches(vector<Batch>& batches)
{
    // Remove batches that have finished.
    DeleteFinishedBatches(batches);

    for (Batch& batch : batches)
    {
        // Update the TimeCode with the amount of time
        // remaining.
        UpdateRemaining(batch);

        cout << batch.id << " time remaining: " << batch.remaining->ToString() << endl;
    }

    cout << batches.size() << " batches being tracked." << endl;
}

void DeleteAllBatches(vector<Batch>& batches)
{
    for (Batch& batch : batches)
    {
        // Delete every heap-allocated TimeCode.
        delete batch.remaining;
    }

    batches.clear();
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    vector<Batch> batches;

    char option;

    while (true)
    {
        cout << "Choose an option: (A)dd, (V)iew Current Items, " << "(Q)uit: ";

        cin >> option;

        if (option == 'a' || option == 'A')
        {
            AddBatch(batches);
        }
        else if (option == 'v' || option == 'V')
        {
            ViewBatches(batches);
        }
        else if (option == 'q' || option == 'Q')
        {
            break;
        }
        else
        {
            cout << "Invalid option." << endl;
        }
    }

    // Clean up every remaining heap allocation before exiting.
    DeleteAllBatches(batches);

    return 0;
}