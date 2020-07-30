import random
import sys


class HashTable:
    """Python Implementation of Multiplicative Hash Table
    """

    def __init__(self, size):
        """Constructor of HashTable

        Args:
            size (int): the size of hash table constructed
        """
        
        self.sigma = random.uniform(0.5, 1.0)
        self.dict = dict()
        self.m = size

    def _hashFunc(self, key):
        """

        Args:
            key (int): key before hash function

        Returns:
            int: the key to the hash table
        """

        temp = self.sigma * key
        return int(self.m * (temp - int(temp)))

    def insert(self, key, data):
        """Insert a key-data pair into the hash table

        Args:
            key ([int]): key of data inserted
            data (various): data inserted
        """

        i = self._hashFunc(key)
        self.dict[i] = data

    def member(self, key):
        """Check if the key exists in hash table

        Args:
            key ([int]): key to be checked

        Returns:
            boolean: whether the key exists in hash table
        """

        return self.dict.get(self._hashFunc(key)) is not None

    def retrieve(self, key):
        """Retrieve data from hash table

        Args:
            key (int): key of data retrieved

        Returns:
            various: data retrieved
        """

        return self.dict.get(self._hashFunc(key))

# File Input and Preprocess
fileName = sys.argv[1]
sumValue = int(sys.argv[2])
with open(fileName, "r") as f:
    content = f.readlines()
data = [int(x.strip()) for x in content]

# Put all data into a hash-table-based checklist
thirdValue = HashTable(len(data) * random.randint(100, 1000))
for i in range(len(data)):
    thirdValue.insert(data[i], True)

# Compute
accessRecord = set() # The Record Set for Valid Pairs
result = 0 # The Result Counter
for i in range(len(data)):
    for j in range(i+1, len(data)):
        diff = sumValue - (data[i] + data[j])

        # Avoid Duplication
        if data[i] == data[j] or data[i] == diff or data[j] == diff:
            continue

        # Avoid Re-access
        if accessRecord.issuperset(set([data[i], data[j], diff])):
            continue

        # Check If The Pair Is Valid
        if thirdValue.member(diff):
            print("(%d, %d, %d)" % (data[i], data[j], diff))
            result += 1
            accessRecord.update(set([data[i], data[j], diff]))

# Report If There Is No Result
if result == 0:
    print("No triplet adds up to %d" % sumValue)