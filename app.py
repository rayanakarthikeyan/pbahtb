import streamlit as st
import pandas as pd
import subprocess
import os

st.set_page_config(page_title="Dynamic Hash Table Analyzer", layout="wide")

st.title("🧮 Dynamic Hash Table Analyzer")
st.markdown("Visualize how different collision resolution techniques perform under varying load factors and data distributions.")

# --- File selector ---
data_file = st.selectbox(
    "Select dataset",
    ["random_keys.txt", "skewed_keys.txt", "uniform_keys.txt"]
)

technique = st.selectbox(
    "Select Collision Resolution Technique",
    ["Separate Chaining", "Linear Probing", "Quadratic Probing", "Double Hashing"]
)

load_factor = st.slider("Select Load Factor", 0.1, 1.0, 0.5, 0.1)

if st.button("Run Analysis"):
    # Compile and run C program
    try:
        os.system("gcc src/hash_table.c -o analyzer")
        result = subprocess.run(
            ["./analyzer", technique.replace(" ", "_"), data_file, str(load_factor)],
            capture_output=True, text=True
        )
        output = result.stdout.strip()
        st.success("✅ Analysis Complete")
        st.code(output)

        # Example visualization placeholder
        st.subheader("📊 Collision Statistics")
        df = pd.DataFrame({
            "Technique": [technique],
            "Load Factor": [load_factor],
            "Collisions": [int(output.split()[-1]) if output.split()[-1].isdigit() else 0]
        })
        st.bar_chart(df.set_index("Technique")["Collisions"])
    except Exception as e:
        st.error(f"❌ Error running analyzer: {e}")
