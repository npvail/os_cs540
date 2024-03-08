import random

# Initialization of the Process class with unique identifier, number of lottery tickets, and starting probability
class Process:
    def __init__(self, process_id, num_tickets):
        self.process_id = process_id
        self.num_tickets = num_tickets
        self.probability = 0

# Initialization of the Scheduler class with an empty list to store processes
class Scheduler:
    def __init__(self):
        self.processes = []
    
    # Add a process to the scheduler
    def add_process(self, process):
        
        self.processes.append(process)
    # Allocate lottery tickets based on the number of tickets each process has
    def allocate_tickets(self):
        total_tickets = sum(process.num_tickets for process in self.processes)
        # Calculate the probability of winning for each process based on its tickets
        for process in self.processes:
            process.probability = process.num_tickets / total_tickets
    # Display the current state of the scheduler
    def display_state(self):
        print("State of the scheduler:")
        for process in self.processes:
            print(f"Process {process.process_id}: {process.num_tickets} tickets | Probability: {process.probability:.2f}")
        print()
    # Randomly select a winner based on the allocated probabilities
    def select_winner(self):
        winner_ticket = random.uniform(0, 1)
        current_probability = 0

        for process in self.processes:
            current_probability += process.probability
            # Return the winning process when the random number falls within its probability range
            if winner_ticket <= current_probability:
                return process



if __name__ == "__main__":
    # Example usage
    process1 = Process(1, 150)
    process2 = Process(2, 200)
    process3 = Process(3, 100)
    scheduler = Scheduler()
    scheduler.add_process(process1)
    scheduler.add_process(process2)
    scheduler.add_process(process3)

    # Display the state after allocating tickets
    scheduler.allocate_tickets()
    scheduler.display_state()

    # Select and print the winner based on the lottery ticket selection
    winner_process = scheduler.select_winner()
    print(f"Process {winner_process.process_id} wins the lottery!")
