/*
 * A Factory design pattern.
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * "character_t" defines the interface to "objects" that will be created by the factory.
 */
typedef struct character_s character_t;

struct character_s {
    void (*operation)(character_t *);
};

/*
 * "character_factory_t" declares the production function that should return
 * "character_t" objects.
 */
typedef struct character_factory_s character_factory_t;

struct character_factory_s {
    character_t *(*factory_method)(void);
};

character_factory_t *new_factory(character_t *(*factory_method)(void));
character_t *new_citizen(void);
character_t *new_spy(void);
character_t *new_case_officer(void);
character_t *new_counterintelligence_officer(void);
void operation_citizen(character_t *citizen);
void operation_spy(character_t *spy);
void operation_case_officer(character_t *case_officer);
void operation_counterintelligence_officer(character_t *counterintelligence_officer);

int main(void)
{
    character_factory_t *factory;
    character_t *a_citizen;
    character_t *a_spy;
    character_t *a_case_officer;
    character_t *a_counterintelligence_officer;

    factory = new_factory(new_citizen);
    a_citizen = factory->factory_method();
    a_citizen->operation(a_citizen);
    free(factory);
    free(a_citizen);

    factory = new_factory(new_spy);
    a_spy = factory->factory_method();
    a_spy->operation(a_spy);
    free(factory);
    free(a_spy);

    factory = new_factory(new_case_officer);
    a_case_officer = factory->factory_method();
    a_case_officer->operation(a_case_officer);
    free(factory);
    free(a_case_officer);

    factory = new_factory(new_counterintelligence_officer);
    a_counterintelligence_officer = factory->factory_method();
    a_counterintelligence_officer->operation(a_counterintelligence_officer);
    free(factory);
    free(a_counterintelligence_officer);

    exit(EXIT_SUCCESS);
}

character_factory_t *new_factory(character_t *(*factory_method)(void))
{
    character_factory_t *factory;

    factory = (character_factory_t *) malloc(sizeof(character_factory_t));
    factory->factory_method = factory_method;

    return factory;
}

character_t *new_citizen(void)
{
    character_t *citizen;

    citizen = (character_t *) malloc(sizeof(character_t));
    citizen->operation = operation_citizen;

    return citizen;
}

character_t *new_spy(void)
{
    character_t *spy;

    spy = (character_t *) malloc(sizeof(character_t));
    spy->operation = operation_spy;

    return spy;
}

character_t *new_case_officer(void)
{
    character_t *case_officer;

    case_officer = (character_t *) malloc(sizeof(character_t));
    case_officer->operation = operation_case_officer;

    return case_officer;
}

character_t *new_counterintelligence_officer(void)
{
    character_t *counterintelligence_officer;

    counterintelligence_officer = (character_t *) malloc(sizeof(character_t));
    counterintelligence_officer->operation = operation_counterintelligence_officer;

    return counterintelligence_officer;
}

void operation_citizen(character_t *citizen)
{
    printf("Operation of a citizen...\n");
}

void operation_spy(character_t *spy)
{
    printf("Operation of a spy...\n");
}

void operation_case_officer(character_t *case_officer)
{
    printf("Operation of a case officer...\n");
}

void operation_counterintelligence_officer(character_t *counterintelligence_officer)
{
    printf("Operation of a counterintelligence_officer...\n");
}
