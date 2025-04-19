import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns


df = pd.read_csv("program_data.csv")
df.columns = df.columns.str.strip()

df["i_cache_miss_ratio"] = df["I-Cache Misses"] / df["Instructions"]
df["branches_per_inst"] = df["Branches Taken"] / df["Instructions"]
df["branches_taken_per_branches"] = df["Branches Taken"] / df["Branches"]
df["rvc_ratio"] = df["RVC Instructions"] / df["Instructions"]
df["cycles_per_instruction"] = df["Cycles"] / df["Instructions"]
df["is_exploit"] = df["Program"].str.contains("exploit").astype(int)

sns.set(style="whitegrid")
plt.figure(figsize=(14, 8))

plt.subplot(2, 3, 1)
sns.barplot(data=df, x="Program", y="i_cache_miss_ratio", hue="is_exploit", palette="Set2")
plt.title("I-Cache Misses per Instruction")
plt.xticks(rotation=20)

plt.subplot(2, 3, 2)
sns.barplot(data=df, x="Program", y="branches_per_inst", hue="is_exploit", palette="Set2")
plt.title("Branches Taken per Instruction")
plt.xticks(rotation=20)

plt.subplot(2, 3, 3)
sns.barplot(data=df, x="Program", y="rvc_ratio", hue="is_exploit", palette="Set2")
plt.title("RVC Instruction Ratio")
plt.xticks(rotation=20)

plt.subplot(2, 3, 4)
sns.barplot(data=df, x="Program", y="branches_taken_per_branches", hue="is_exploit", palette="Set2")
plt.title("CPI Comparison")
plt.xticks(rotation=20)

plt.subplot(2, 3, 5)
sns.barplot(data=df, x="Program", y="CPI", hue="is_exploit", palette="Set2")
plt.title("Branches Taken Branches Ratio")
plt.xticks(rotation=20)

plt.subplot(2, 3, 6)
sns.barplot(data=df, x="Program", y="Jumps", hue="is_exploit", palette="Set2")
plt.title("Jumps")
plt.xticks(rotation=20)

# Layout adjustment
plt.tight_layout()
plt.show()
