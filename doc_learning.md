---
title: Machine Learning Module
tags:
keywords: learning, engine, set covering machine, SCM, kover, genomics, k-mer, machine learning
last_updated: March 27, 2016
summary: "Overview of the machine learning functionality"
---

## Learning models

This command is used to learn a model from a Kover dataset. It provides an interface on the Set Covering Machine algorithm.

```
usage: kover learn [-h] --dataset DATASET --split SPLIT --model-type
                   {conjunction,disjunction} [{conjunction,disjunction} ...]
                   --p P [P ...] --max-rules MAX_RULES
                   [--max-equiv-rules MAX_EQUIV_RULES]
                   [--hp-choice {bound,cv,none}] [--bound-delta BOUND_DELTA]
                   [--bound-max-genome-size BOUND_MAX_GENOME_SIZE]
                   [--random-seed RANDOM_SEED] [--n-cpu N_CPU]
                   [--output-dir OUTPUT_DIR] [-x] [-v]

Learn a model from data

optional arguments:
  -h, --help            show this help message and exit
  --dataset DATASET     The Kover dataset from which to learn.
  --split SPLIT         The identifier of the split of the dataset to use for
                        learning.
  --model-type {conjunction,disjunction} [{conjunction,disjunction} ...]
                        Hyperparameter: The type of model to learn,
                        conjunction (logical-AND) or disjunction (logical-OR).
                        You can specify multiple space separated values.
  --p P [P ...]         Hyperparameter: The value of the trade-off parameter
                        in the rule scoring criterion. You can specify
                        multiple space separated values.
  --max-rules MAX_RULES
                        The maximum number of rules that can be included in
                        the model.
  --max-equiv-rules MAX_EQUIV_RULES
                        The maximum number of equivalent rules to report for
                        each rule in the model. This only affects model
                        interpretation. Use the default unless you expect that
                        the rules in the model will be equivalent to more than
                        10000 other rules.
  --hp-choice {bound,cv,none}
                        The strategy used to select the best values for
                        hyperparameters. The default is k-fold cross-
                        validation, where k is the number of folds defined in
                        the split. Other strategies, such as bound selection
                        are available. Using none selects the first value
                        specified for each hyperparameter.
  --bound-delta BOUND_DELTA
                        The probabilistic bound on the error rate will be
                        valid with probability 1-delta. The default value is
                        0.05.
  --bound-max-genome-size BOUND_MAX_GENOME_SIZE
                        The maximum size, in base pairs, of anygenome in the
                        dataset. If you are unsure about this value, you
                        should use an over-estimate. This will only affect the
                        tightness of the bound on the error rate. By default
                        number of k-mers in the dataset is used.
  --random-seed RANDOM_SEED
                        The random seed used for any random operation. Set
                        this if only if you require that the same random
                        choices are made between repeats.
  --n-cpu N_CPU         The number of CPUs used to select the hyperparameter
                        values. Make sure your computer has enough RAM to
                        handle multiple simultaneous trainings of the
                        algorithm and that your storage device will not be a
                        bottleneck (simultaneous reading).
  --output-dir OUTPUT_DIR
                        The directory in which to store Kover's output. It
                        will be created if it does not exist.
  -x, --progress        Shows a progress bar for the execution.
  -v, --verbose         Sets the verbosity level.
```